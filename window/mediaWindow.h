//
// Created by chenz on 2022/11/12.
//

#ifndef FFMPEG_TEST_MEDIAWINDOW_H
#define FFMPEG_TEST_MEDIAWINDOW_H

#define SDL_MAIN_HANDLED
extern "C" {
#include <SDL.h>
};
#include <string>

class MediaWindow {
    SDL_Window* pWindow = nullptr;
    SDL_Renderer* pRender = nullptr;
    SDL_Texture* texture =  nullptr;
    int winQuit = 1;
public:
    MediaWindow(std::string title,int x,int y,int w,int h);
    void setRenderSize(int width,int height);
    void playWindow();
    void closeWindow();
};



#endif //FFMPEG_TEST_MEDIAWINDOW_H
