//
// Created by chenz on 2022/11/11.
//

#include <iostream>
#include "MediaControl.h"

MediaControl::MediaControl() {}
MediaControl::~MediaControl() {}

void MediaControl::openFmt(std::string path) {
    int ret = avformat_open_input(&this->fmt,path.c_str(),NULL,NULL);
    std::cout << ret << std::endl;
}
