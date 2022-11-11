//
// Created by chenz on 2022/11/11.
//

#include <iostream>
#include "MediaControl.h"

MediaControl::MediaControl() {}
MediaControl::~MediaControl() {}

void MediaControl::openFmt(std::string path) {
    int ret = avformat_open_input(&this->fmt,path.c_str(),NULL,NULL);
    std::cout << "avformat_open_input call: ret = " << ret << std::endl;
    // 对流信息提取
    ret = avformat_find_stream_info(this->fmt,NULL);
    std::cout << "avformat_find_stream_info: ret = " << ret << std::endl;

    this->idx = av_find_best_stream(this->fmt,AVMEDIA_TYPE_VIDEO,-1,-1,NULL,0);
    std::cout << "av_find_best_stream: ret = " << this->idx << std::endl;

    this->inStream = this->fmt->streams[this->idx];
    this->dec = avcodec_find_decoder(this->inStream->codecpar->codec_id);
    // 创建解码器上下文
    this->decCtx =  avcodec_alloc_context3(this->dec);

    // 从视频流中拷贝解码器参数岛解码器上下文
    ret = avcodec_parameters_to_context(this->decCtx,this->inStream->codecpar);
    std::cout << "avcodec_parameters_to_context: ret = " << ret << std::endl;

    // 绑定解码器 和 解码器上下文
    ret = avcodec_open2(this->decCtx,this->dec, nullptr);
    std::cout << "avcodec_open2: ret = " << ret << std::endl;



}
