//
// Created by chenz on 2022/11/12.
//

#ifndef FFMPEG_TEST_PLAYWINDOW_H
#define FFMPEG_TEST_PLAYWINDOW_H

#define SDL_MAIN_HANDLED
extern "C" {
#include <SDL.h>
};

#include <string>
class PlayWindow {

    SDL_Window* pWindow = nullptr;
    SDL_Renderer* pRender = nullptr;
    SDL_Texture* texture =  nullptr;
    int winQuit = 1;

public:
    PlayWindow();
    ~PlayWindow();
    void setWindowInfo(std::string title,int x,int y,int w,int h);
    void windowShow();
    void windowPlayMedia();
    void windowClose();
};


#endif //FFMPEG_TEST_PLAYWINDOW_H
