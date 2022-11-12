#include <iostream>
#include "window/windowControl.h"
#include "window/MediaControl.h"


int main() {

    WindowControl wCtrl;
    MediaControl mediaControl;
    wCtrl.createWindow("play_test",100,100,600,400);
    wCtrl.playWindow();


//    wCtrl.createWindow();
//    MediaRect mediaRect = mediaControl.openFmt("./test.mp4");
//
//    wCtrl.createTexture(mediaRect.width,mediaRect.height);
//    wCtrl.playWindow();



    return 0;
}
