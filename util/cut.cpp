#include <string>
#include <iostream>
extern "C" {
#include <libavformat/avformat.h>
}

using namespace std;

static string errInfo(int errCode) {
    char errStr[256] = { 0 };
    av_strerror(errCode, errStr, sizeof(errStr));
    return string(errStr);
}

void cut() {
    int ret = -1;
    const string srcFile = "./test.mp4";
    const string distFile = "./test_out_cut.mp4";
    int startTime = 120;
    int endTime = atof("100");

    AVFormatContext* srcFmtCtx = nullptr;
    AVFormatContext* distFmtCtx = nullptr;
    const AVOutputFormat*  guessFmt = nullptr;
    AVPacket avPacket;
    int* streamMap = nullptr;
    ret = avformat_open_input(&srcFmtCtx,srcFile.c_str(), nullptr, nullptr);
    avformat_alloc_output_context2(&distFmtCtx, nullptr, nullptr,distFile.c_str());

    streamMap = static_cast<int *>(av_calloc(srcFmtCtx->nb_streams, sizeof(int)));
    int stream_index = 0;
    for(int i = 0; i < srcFmtCtx->nb_streams; i++) {

        AVStream* srcStream = nullptr;
        AVStream* distStream = nullptr;
        AVStream *inStream = srcFmtCtx->streams[i];
        AVCodecParameters* inCodePar = inStream->codecpar;
        if(inCodePar->codec_type != AVMEDIA_TYPE_VIDEO &&
           inCodePar->codec_type != AVMEDIA_TYPE_AUDIO &&
           inCodePar->codec_type != AVMEDIA_TYPE_SUBTITLE) {
            streamMap[i] = -1;
            continue;
        }
        streamMap[i] = stream_index++;
        distStream = avformat_new_stream(distFmtCtx, nullptr);
        srcStream = srcFmtCtx->streams[i];
        avcodec_parameters_copy(distStream->codecpar,srcStream->codecpar);
        //设置成0，可以根据媒体文件自动适配解码器
        distStream->codecpar->codec_tag = 0;

    }

    ret = avio_open2(&distFmtCtx->pb,distFile.c_str(),AVIO_FLAG_WRITE, nullptr, nullptr);
    ret = avformat_write_header(distFmtCtx, nullptr);

    // 告诉ffmpeg 从什么时间点开始截取数据
    // 音频是流式的，可以从任意时间点截取
    // 视频分成I帧，B帧，P帧。B帧或P帧没法单独播放，时间点要前找或后找，找到最近的I帧
    //2.操作哪个流，-1 ffmpeg 帮忙选择默认流
    //4.向后查找I帧
    av_seek_frame(srcFmtCtx,-1, startTime*AV_TIME_BASE,AVSEEK_FLAG_BACKWARD);

    // 剪辑要记录原始时间戳
    int64_t* dts_start_time = static_cast<int64_t *>(av_calloc(srcFmtCtx->nb_streams, sizeof(int64_t)));
    int64_t* pts_start_time = static_cast<int64_t *>(av_calloc(srcFmtCtx->nb_streams, sizeof(int64_t)));
    for(int i = 0 ; i< srcFmtCtx->nb_streams; i++) {
        dts_start_time[i] = -1;
        pts_start_time[i] = -1;
    }

    while (av_read_frame(srcFmtCtx,&avPacket) >= 0) {
        if(pts_start_time[avPacket.stream_index] == -1 && avPacket.pts) {
            pts_start_time[avPacket.stream_index] = avPacket.pts;
        }
        if(dts_start_time[avPacket.stream_index] == -1 && avPacket.dts) {
            dts_start_time[avPacket.stream_index] = avPacket.dts;
        }

        if(streamMap[avPacket.stream_index] < 0) {
            av_packet_unref(&avPacket);
            continue;
        }

        // 时间戳校准
        avPacket.pts = avPacket.pts - pts_start_time[avPacket.stream_index];
        avPacket.dts = avPacket.dts - dts_start_time[avPacket.stream_index];

        AVStream* srcStream = srcFmtCtx->streams[avPacket.stream_index];
        avPacket.stream_index = streamMap[avPacket.stream_index];
        AVStream* distStream = distFmtCtx->streams[avPacket.stream_index];

        av_packet_rescale_ts(&avPacket,srcStream->time_base,distStream->time_base);

        avPacket.pos = -1;
        av_interleaved_write_frame(distFmtCtx, &avPacket);
        av_packet_unref(&avPacket);

    }

    av_write_trailer(distFmtCtx);

    // 释放资源
    return;
}