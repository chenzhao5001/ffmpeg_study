#include <iostream>
#include "PlayWindow.h"
#include "MediaControl.h"

PlayWindow::PlayWindow() {
    SDL_Init(SDL_INIT_VIDEO);

}
PlayWindow::~PlayWindow(){
    if(pWindow) {
        SDL_DestroyWindow(pWindow);
        pWindow = nullptr;
    }
    if(pRender) {
        SDL_DestroyRenderer(pRender);
        pRender = nullptr;
    }
    if(pTexture) {
        SDL_DestroyTexture(pTexture);
        pTexture = nullptr;
    }
    SDL_Quit();
}

void PlayWindow::mediaInit() {

//    mediaControl.setWindow(pWindow);
}

void PlayWindow::setWindowInfo(std::string title,int x,int y,int w,int h) {
    pWindow = SDL_CreateWindow("title",x,y,w,h,
                               SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    pRender = SDL_CreateRenderer(pWindow,-1,0);
    SDL_SetRenderDrawColor(pRender,255,0,0,255);
    SDL_RenderClear(pRender);
    SDL_RenderPresent(pRender);

    pTexture = SDL_CreateTexture(pRender,SDL_PIXELFORMAT_ABGR8888,
                      SDL_TEXTUREACCESS_TARGET,600,450);

    windowCell.pWindow = pWindow;
    windowCell.pRender = pRender;
    windowCell.pTexture = pTexture;
    mediaControl.setWindow(windowCell);

}

void PlayWindow::windowPlayMedia() {
    mediaControl.openFmt(playFile);
}

void PlayWindow::setPlayFilePath(std::string path) {
    playFile = path;
}

void PlayWindow::windowShow() {
    SDL_Event mWinEv;
    do {
        std::cout << "1111" << std::endl;
//        SDL_WaitEvent(&mWinEv);
        SDL_PollEvent(&mWinEv);
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