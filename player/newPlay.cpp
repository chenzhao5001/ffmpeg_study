//
// Created by chenz on 2022/11/9.
//

#include <stdio.h>
#include "newPlay.h"

NewPlayer::NewPlayer() {
    SDL_Init(SDL_INIT_VIDEO);

    mWindow = SDL_CreateWindow("测试",100,100,640,480,SDL_WINDOW_OPENGL);
    mRender = SDL_CreateRenderer(mWindow,-1,0);

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


}


