//
// Created by chenz on 2022/11/9.
//

#ifndef FFMPEG_TEST_NEWPLAY_H
#define FFMPEG_TEST_NEWPLAY_H

extern "C" {
#include <libavutil/log.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <SDL.h>
};

#include "stdio.h"

class NewPlayer {

    SDL_Window* mWindow = NULL;
    SDL_Renderer* mRender = NULL;

    NewPlayer();
    ~NewPlayer();
};

#endif //FFMPEG_TEST_NEWPLAY_H
