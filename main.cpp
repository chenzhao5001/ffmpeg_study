#include <iostream>
#include "window/windowControl.h"
#include "window/MediaControl.h"


void foo(int **p) {
    *p = new int;
    (**p) = 200;
}

int main() {

    int* p = nullptr;
    foo(&p);
    std::cout << *p << std::endl;
    std::cout << p << std::endl;




    WindowControl wCtrl;

    MediaControl mediaControl;
    mediaControl.openFmt("./test.mp4");

    wCtrl.createWindow();
    wCtrl.playWindow();


    return 0;
}
