#include "windowControl.h"

WindowControl::WindowControl() {
    SDL_Init(SDL_INIT_VIDEO);

}
WindowControl::~WindowControl() {}

void WindowControl::createWindow() {
    pWindow = SDL_CreateWindow("测试",100,100,640,480,SDL_WINDOW_OPENGL);
    pRender = SDL_CreateRenderer(pWindow,-1,0);
    SDL_SetRenderDrawColor(pRender,255,0,0,255);
    SDL_RenderClear(pRender);
    SDL_RenderPresent(pRender);
}

void WindowControl::playWindow() {
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
void  WindowControl::destroyWindow() {
    this->winQuit = 0;
}
