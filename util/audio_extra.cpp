//
// Created by chenz on 2022/11/12.
//
#include <string>
#include <iostream>
extern "C" {
#include <libavformat/avformat.h>
}


using namespace std;

void extra_audio() {

    int ret = -1;
    const string filePath = "./test.mp4";
    AVFormatContext* avFormatContext = nullptr;

    // 3.AVInputFormat 指定容器格式，不设置按照后缀解析。
    // 4.特殊选项设置？
    ret = avformat_open_input(&avFormatContext,filePath.c_str(), nullptr, nullptr);
    cout << ret << endl;

    return;
}