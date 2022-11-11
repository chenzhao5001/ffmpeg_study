#include <iostream>

extern "C" {
#include <libavutil/log.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
};

#include "window/windowControl.h"


int main() {
    WindowControl wCtrl;
    wCtrl.createWindow();
    wCtrl.playWindow();

    return 0;
}
