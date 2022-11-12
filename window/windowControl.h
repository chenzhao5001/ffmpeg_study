//
// Created by chenz on 2022/11/11.
//

#ifndef FFMPEG_TEST_WINDOWCONTROL_H
#define FFMPEG_TEST_WINDOWCONTROL_H

#include <string>
#include "mediaWindow.h"
class WindowControl {

public: MediaWindow* mediaWindow = nullptr;

public:
    WindowControl();
    ~WindowControl();
    MediaWindow* createWindow(std::string string,int x,int y,int w,int h);
    void createTexture(int width,int height);
    void playWindow();
    void destroyWindow();
private:
    int winQuit = 1;
};


#endif //FFMPEG_TEST_WINDOWCONTROL_H
