//
// Created by chenz on 2022/11/11.
//

#ifndef FFMPEG_TEST_MEDIACONTROL_H
#define FFMPEG_TEST_MEDIACONTROL_H

extern "C" {
#include <libavutil/log.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavcodec/avcodec.h>
};

#include <string>


class MediaControl {

public:
    MediaControl();
    ~MediaControl();
    void openFmt(std::string path);

private:
    AVFormatContext* fmt = nullptr;
    int idx = -1; //流id
    AVStream* inStream = nullptr; // 输入流
    const AVCodec* dec = nullptr;  //解码器
    AVCodecContext* decCtx = nullptr; // 解码器上下文


};


#endif //FFMPEG_TEST_MEDIACONTROL_H
