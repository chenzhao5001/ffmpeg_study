//
// Created by chenz on 2022/11/12.
//

#include "PlayWindow.h"
#include "MediaControl.h"

PlayWindow::PlayWindow() {

}
PlayWindow::~PlayWindow(){

}


void PlayWindow::setWindowInfo(std::string title,int x,int y,int w,int h) {
    pWindow = SDL_CreateWindow("title",x,y,w,h,
                               SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    pRender = SDL_CreateRenderer(pWindow,-1,0);
    SDL_SetRenderDrawColor(pRender,255,0,0,255);
    SDL_RenderClear(pRender);
    SDL_RenderPresent(pRender);
}

void PlayWindow::windowPlayMedia() {
    mediaControl.openFmt(playFile);
}

void PlayWindow::setPlayFilePath(std::string path) {
    playFile = path;
}

void PlayWindow::windowShow() {
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
    } while (winQuit);
}
void PlayWindow::windowClose() {
    winQuit = 0;
}