#include <iostream>

extern "C" {
#include <libavutil/log.h>
#include <libavformat/avio.h>

};

#include "util/io_test.h"

void goo();
void foo();


//av_log，第一个参数设置成null或继承自avclass的对象

int main() {
    std::cout << "Hello, World!" << std::endl;
    av_log_set_level(AV_LOG_DEBUG);  //设置日志级别
//    openDir("./");
    return 0;
}
