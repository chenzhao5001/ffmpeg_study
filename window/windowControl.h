//
// Created by chenz on 2022/11/11.
//

#ifndef FFMPEG_TEST_WINDOWCONTROL_H
#define FFMPEG_TEST_WINDOWCONTROL_H
#define SDL_MAIN_HANDLED
extern "C" {
#include <SDL.h>
};

class WindowControl {
    SDL_Window* pWindow = NULL;
    SDL_Renderer* pRender = NULL;
public:
    WindowControl();
    ~WindowControl();
    void createWindow();
    void playWindow();
    void destroyWindow();
private:
    int winQuit = 1;
};


#endif //FFMPEG_TEST_WINDOWCONTROL_H
