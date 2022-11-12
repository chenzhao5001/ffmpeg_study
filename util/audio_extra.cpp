//
// Created by chenz on 2022/11/12.
//
#include <string>
#include <iostream>
extern "C" {
#include <libavformat/avformat.h>
}


using namespace std;

string errInfo(int errCode) {
    char errStr[256] = { 0 };
    av_strerror(errCode, errStr, sizeof(errStr));
    return string(errStr);
}

void extra_audio() {

    int ret = -1;
    const string filePath = "./test.mp4";
    const string outputFile = "./test_out";
    AVFormatContext* avFormatContext = nullptr;
    AVFormatContext* oAVFormatContext = nullptr;

    // 3.AVInputFormat 指定容器格式，不设置按照后缀解析。
    // 4.特殊选项设置？
    ret = avformat_open_input(&avFormatContext,filePath.c_str(), nullptr, nullptr);
    cout << ret << endl;

    //3.指定特定流，不知道设置-1， 4, htl, program 分片，一般填-1，5，优先使用的解码器
    int index = av_find_best_stream(avFormatContext,AVMEDIA_TYPE_AUDIO,-1,-1, nullptr,0);
    cout << index << endl;

    // 输出文件上下文
    oAVFormatContext = avformat_alloc_context();
    cout << "avformat_alloc_context ret = " << oAVFormatContext << endl;

    // 减少设置参数复杂度
    const AVOutputFormat*  avOutputFormat = av_guess_format(nullptr,outputFile.c_str(), nullptr);
    cout << "av_guess_format ret = " << avOutputFormat << endl;
    oAVFormatContext->oformat = avOutputFormat;

    // 为目标文件设设置流
    AVStream* outStream =  avformat_new_stream(oAVFormatContext, nullptr);
    cout << "avformat_new_stream ret = " << outStream << endl;

    //获取输入流
    AVStream* inStream = avFormatContext->streams[index];
    //拷贝流
    ret = avcodec_parameters_copy(outStream->codecpar,inStream->codecpar);
    cout << "avcodec_parameters_copy ret = " << ret << endl;

    //设置成0，可以根据媒体文件自动适配解码器
    outStream->codecpar->codec_tag = 0;

    //绑定目标文件 4.回调函数，5，私有协议选项。
    ret = avio_open2(&oAVFormatContext->pb,outputFile.c_str(),AVIO_FLAG_WRITE, nullptr, nullptr);
    cout << "avio_open2 ret = " << ret << endl;
    cout << errInfo(ret) << endl;

    // 写多媒体头到目标文件
    ret = avformat_write_header(oAVFormatContext, nullptr);
    cout << "avformat_write_header ret = " << ret << endl;

    //读取频频数据，并写入
    AVPacket avPacket;
    while (av_read_frame(avFormatContext,&avPacket) >=0) {
        if(avPacket.stream_index == index) {
            // 改变时间戳,除不尽，算近似值
            // 时间基（毫秒，微妙）
            avPacket.pts = av_rescale_q_rnd(avPacket.pts,inStream->time_base,outStream->time_base,
                                            static_cast<AVRounding>(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
            avPacket.dts = avPacket.pts;
            avPacket.duration = av_rescale_q(avPacket.duration,inStream->time_base,outStream->time_base);
            avPacket.stream_index = 0;
            avPacket.pos = -1;
            av_interleaved_write_frame(oAVFormatContext,&avPacket);
            // 需要减少引用计数，否则有泄露。
            av_packet_unref(&avPacket);
        }
    }

    av_write_trailer(oAVFormatContext);

    // 释放资源
    return;
}