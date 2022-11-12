#include "window/PlayWindow.h"

int main() {

    PlayWindow playWindow;
    playWindow.setWindowInfo("hello", 100,100,600,400);
    playWindow.setPlayFilePath("./test.mp4");
    playWindow.windowPlayMedia();


    playWindow.windowShow();
    return 0;
}
