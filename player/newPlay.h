//
// Created by chenz on 2022/11/9.
//

#ifndef FFMPEG_TEST_NEWPLAY_H
#define FFMPEG_TEST_NEWPLAY_H
#define SDL_MAIN_HANDLED

extern "C" {
//#include <libavutil/log.h>
//#include <libavformat/avformat.h>
//#include <libavcodec/avcodec.h>
#include <SDL.h>
};

#include "stdio.h"

class NewPlayer {

    SDL_Window* pWindow = NULL;
    SDL_Renderer* pRender = NULL;

public:
    NewPlayer();
    ~NewPlayer();
private:
};

#endif //FFMPEG_TEST_NEWPLAY_H
