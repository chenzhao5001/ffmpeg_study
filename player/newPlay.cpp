#include "newPlay.h"


NewPlayer::NewPlayer() {
    SDL_Init(SDL_INIT_VIDEO);

    pWindow = SDL_CreateWindow("测试",100,100,640,480,SDL_WINDOW_OPENGL);
    pRender = SDL_CreateRenderer(pWindow,-1,0);

    int quit = 1;
    do {
        SDL_Event mWinEv;
        SDL_WaitEvent(&mWinEv);
        switch (mWinEv.type) {
            case SDL_QUIT:
                quit = 0;
                break;
            default:
                break;
        }
    } while (quit);
}

NewPlayer::~NewPlayer() {
    if(pWindow) {
        SDL_DestroyWindow(pWindow);
    }
    if(pRender) {
        SDL_DestroyRenderer(pRender);
    }
}


