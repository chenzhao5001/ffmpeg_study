//
// Created by chenz on 2022/11/9.
//

extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavutil/log.h>
}

#include "audio_control.h"

int getAudioStream(char* src,char* dst) {
    int ret = -1;
    AVFormatContext* pAvFormatContext = NULL;
    // src 支持本地 和 远端
    // AVInputFormat 指定多媒体文件格式，如果不指定按后缀读取，如果对应不上会发生错误。
    // AVDictionary key,value值，设置特殊选项
    // return <0 错误  >0成功

    if((ret = avformat_open_input(&pAvFormatContext,src,NULL,NULL)) < 0) {
        av_log(NULL,AV_LOG_ERROR,"%s\n",av_err2str(ret));
        return ret;
    }
    return 0;
}
