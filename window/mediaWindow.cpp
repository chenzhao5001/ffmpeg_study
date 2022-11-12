//
// Created by chenz on 2022/11/12.
//


#include "mediaWindow.h"

MediaWindow::MediaWindow(std::string title,int x,int y,int w,int h) {
    pWindow = SDL_CreateWindow("title",x,y,w,h,
                               SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    pRender = SDL_CreateRenderer(pWindow,-1,0);
    SDL_SetRenderDrawColor(pRender,255,0,0,255);
    SDL_RenderClear(pRender);
    SDL_RenderPresent(pRender);
}

void MediaWindow::setRenderSize(int width,int height) {
    Uint32 pixFormat = SDL_PIXELFORMAT_IYUV; // 像素格式
    SDL_Texture* texture = SDL_CreateTexture(
            pRender,pixFormat, SDL_TEXTUREACCESS_STREAMING, width,height);

}

void MediaWindow::playWindow() {
    do {
        SDL_Event mWinEv;
        SDL_WaitEvent(&mWinEv);
        switch (mWinEv.type) {
            case SDL_QUIT:
                winQuit = 0;
                break;
            default:
                break;
        }
    } while (this->winQuit);
}

void MediaWindow::closeWindow() {
    this->winQuit = 0;
}
