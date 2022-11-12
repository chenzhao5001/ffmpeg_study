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

void remux() {

    int ret = -1;
    const string srcFile = "./test.mp4";
    //这里后缀一定要写对，否则会报错。
    const string distFile = "./test_out.mp4";

    AVFormatContext* srcFmtCtx = nullptr;
    AVFormatContext* distFmtCtx = nullptr;

    const AVOutputFormat*  guessFmt = nullptr;

//    AVStream* srcStream = nullptr;
//    AVStream* distStream = nullptr;

    AVPacket avPacket;
    int index = -1; //stream id

    int* streamMap = nullptr;


    // 3.AVInputFormat 指定容器格式，不设置按照后缀解析。
    // 4.特殊选项设置？
    ret = avformat_open_input(&srcFmtCtx,srcFile.c_str(), nullptr, nullptr);
    cout << ret << endl;



    // 根据目标文件后缀 获取少上下文。
    avformat_alloc_output_context2(&distFmtCtx, nullptr, nullptr,distFile.c_str());

    // 遍历每一路流
    // 多媒体文件中可能有音频流，视频流，字幕流，可能还有meta,meta流视频转换后没有意义了，需要过滤掉。

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

    //绑定目标文件 4.回调函数，5，私有协议选项。
    ret = avio_open2(&distFmtCtx->pb,distFile.c_str(),AVIO_FLAG_WRITE, nullptr, nullptr);
    cout << "avio_open2 ret = " << ret << endl;
    cout << errInfo(ret) << endl;

    // 写多媒体头到目标文件
    ret = avformat_write_header(distFmtCtx, nullptr);
    cout << "avformat_write_header ret = " << ret << endl;

    //读取音频，视频, 字母，并写入
    while (av_read_frame(srcFmtCtx,&avPacket) >= 0) {
        if(streamMap[avPacket.stream_index] < 0) {
            av_packet_unref(&avPacket);
            continue;
        }
        AVStream* srcStream = srcFmtCtx->streams[avPacket.stream_index];
        avPacket.stream_index = streamMap[avPacket.stream_index];
        AVStream* distStream = distFmtCtx->streams[avPacket.stream_index];

        av_packet_rescale_ts(&avPacket,srcStream->time_base,distStream->time_base);

        avPacket.pos = -1;
        av_interleaved_write_frame(distFmtCtx, &avPacket);
        // 需要减少引用计数，否则有泄露。
        av_packet_unref(&avPacket);

    }

    av_write_trailer(distFmtCtx);

    // 释放资源
    return;
}