//
// Created by chenz on 2022/11/9.
//



extern "C" {
#include <libavutil/log.h>
#include <libavformat/avio.h>
}


// avio_open_dir windows 返回 -40 （Function not implement）
void openDir(char* path) {
    AVIODirContext * context = NULL;
    AVDictionary* dictionary = NULL;
    int ret = avio_open_dir(&context,path,&dictionary);
    av_log(NULL,AV_LOG_DEBUG,"open_dir ret = %d",ret);

}