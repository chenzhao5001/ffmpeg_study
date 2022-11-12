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
    const string filePath = "./test.mp4";
    //这里后缀一定要写对，否则会报错。
    const string outputFile = "./test_out.h264";

    AVFormatContext* srcFmtCtx = nullptr;
    AVFormatContext* distFmtCtx = nullptr;

    const AVOutputFormat*  guessFmt = nullptr;
    AVStream* srcStream = nullptr;
    AVStream* distStream = nullptr;

    AVPacket avPacket;






    int index = -1; //stream id


    // 3.AVInputFormat 指定容器格式，不设置按照后缀解析。
    // 4.特殊选项设置？
    ret = avformat_open_input(&srcFmtCtx,filePath.c_str(), nullptr, nullptr);
    cout << ret << endl;

    //3.指定特定流，不知道设置-1， 4, htl, program 分片，一般填-1，5，优先使用的解码器
    index = av_find_best_stream(srcFmtCtx,AVMEDIA_TYPE_VIDEO,-1,-1, nullptr,0);
    cout << index << endl;

    // 输出文件上下文
    distFmtCtx = avformat_alloc_context();
    cout << "avformat_alloc_context ret = " << distFmtCtx << endl;

    // 减少设置参数复杂度
    guessFmt = av_guess_format(nullptr,outputFile.c_str(), nullptr);
    cout << "av_guess_format ret!!!! = " << guessFmt << endl;
    distFmtCtx->oformat = guessFmt;

    // 为目标文件设设置流
    distStream =  avformat_new_stream(distFmtCtx, nullptr);
    cout << "avformat_new_stream ret = " << distStream << endl;

    //获取输入流
    srcStream = srcFmtCtx->streams[index];
    //拷贝流
    ret = avcodec_parameters_copy(distStream->codecpar,srcStream->codecpar);
    cout << "avcodec_parameters_copy ret = " << ret << endl;

    //设置成0，可以根据媒体文件自动适配解码器
    distStream->codecpar->codec_tag = 0;

    //绑定目标文件 4.回调函数，5，私有协议选项。
    ret = avio_open2(&distFmtCtx->pb,outputFile.c_str(),AVIO_FLAG_WRITE, nullptr, nullptr);
    cout << "avio_open2 ret = " << ret << endl;
    cout << errInfo(ret) << endl;

    // 写多媒体头到目标文件
    ret = avformat_write_header(distFmtCtx, nullptr);
    cout << "avformat_write_header ret = " << ret << endl;

    //读取频频数据，并写入
    while (av_read_frame(srcFmtCtx,&avPacket) >=0) {
        if(avPacket.stream_index == index) {
            // 改变时间戳,除不尽，算近似值
            // 时间基（毫秒，微妙）
            avPacket.pts = av_rescale_q_rnd(avPacket.pts,srcStream->time_base,distStream->time_base,
                                            static_cast<AVRounding>(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));

            // 这里音视频不一致，音频dts一定等于pts,视频不一定
            // avPacket.dts = avPacket.pts;
            // 视频要从源数据里获取
            avPacket.dts = av_rescale_q_rnd(avPacket.dts,srcStream->time_base,distStream->time_base,
                                            static_cast<AVRounding>(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));

            avPacket.duration = av_rescale_q(avPacket.duration,srcStream->time_base,distStream->time_base);
            avPacket.stream_index = 0;
            avPacket.pos = -1;
            av_interleaved_write_frame(distFmtCtx,&avPacket);
            // 需要减少引用计数，否则有泄露。
            av_packet_unref(&avPacket);
        }
    }

    av_write_trailer(distFmtCtx);

    // 释放资源
    return;
}