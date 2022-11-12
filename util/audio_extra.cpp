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

    //拷贝流
    AVStream* inStream = avFormatContext->streams[index];
    ret = avcodec_parameters_copy(outStream->codecpar,inStream->codecpar);
    cout << "avcodec_parameters_copy ret = " << ret << endl;

    //设置成0，可以根据媒体文件自动适配解码器
    outStream->codecpar->codec_tag = 0;

    //绑定目标文件 4.回调函数，5，私有协议选项。
    ret = avio_open2(&oAVFormatContext->pb,outputFile.c_str(),AVIO_FLAG_WRITE, nullptr, nullptr);
    cout << "avio_open2 ret = " << ret << endl;
    cout << errInfo(ret) << endl;

    // 写多媒体头到目标文件






    return;
}