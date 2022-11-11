//
// Created by chenz on 2022/11/11.
//

#ifndef FFMPEG_TEST_MEDIACONTROL_H
#define FFMPEG_TEST_MEDIACONTROL_H

extern "C" {
#include <libavutil/log.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
};

#include <string>


class MediaControl {

public:
    MediaControl();
    ~MediaControl();
    void openFmt(std::string path);

private:
    AVFormatContext* fmt = NULL;

};


#endif //FFMPEG_TEST_MEDIACONTROL_H
