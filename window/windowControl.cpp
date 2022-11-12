#include "windowControl.h"
#include "mediaWindow.h"

WindowControl::WindowControl() {
    SDL_Init(SDL_INIT_VIDEO);
}
WindowControl::~WindowControl() {}

void WindowControl::createWindow(std::string title,int x,int y,int w,int h) {
    mediaWindow = new MediaWindow(title,x,y,w,h);
}

void WindowControl::createTexture(int width,int height) {
}
void WindowControl::playWindow() {
    mediaWindow->playWindow();
}
void  WindowControl::destroyWindow() {
    this->winQuit = 0;
}
