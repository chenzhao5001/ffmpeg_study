//
// Created by chenz on 2022/11/9.
//

extern "C" {
#include <libavcodec/codec.h>
#include <libavutil/log.h>
}

#include "codec.h"

void enCode() {
    try {
        //1.输入参数
        //2.查找编解码器

        // ffmpeg查找编解码器的方法有两种 1，通过id 2,通过名字 此处通过名字

        const AVCodec* codec = avcodec_find_encoder_by_name("");
        if(!codec) {
            av_log(NULL,AV_LOG_ERROR,"avcodec_find_encoder_by_name err!");
            throw -10002;
        }

        //3.创建编解码上下文
        //4.设置密码器参数
        //5.编码器 解码器 上下文绑定到一起
        //6.创建输出文件
        //7.创建AVFrame
        //8.创建AVPacket
        //9.生成视频内容
        //10.编码
    } catch (int err) {

    }


}