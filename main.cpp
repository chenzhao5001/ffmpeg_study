#include <iostream>

extern "C" {
#include <libavutil/log.h>
};


void goo();

void foo();

int main() {
    std::cout << "Hello, World!" << std::endl;
    goo();
    foo();
    av_log_set_level(AV_LOG_DEBUG);
    return 0;
}
