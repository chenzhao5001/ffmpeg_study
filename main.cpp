#include <iostream>
#include "window/windowControl.h"
//#include "window/MediaControl.h"

#include "window/PlayWindow.h"


int main() {

    PlayWindow playWindow;
    playWindow.setWindowInfo("hello", 100,100,600,400);

    playWindow.windowShow();


//    WindowControl wCtrl;
//    wCtrl

//    MediaWindow* mediaWindow = wCtrl.createWindow("play_test",100,100,600,400);

//    wCtrl.playWindow();


//    wCtrl.createWindow();
//    MediaRect mediaRect = mediaControl.openFmt("./test.mp4");
//
//    wCtrl.createTexture(mediaRect.width,mediaRect.height);
//    wCtrl.playWindow();



    return 0;
}
