//
// Created by chenz on 2022/11/9.
//

extern "C" {
//#include <libavcodec/codec.h>
#include <libavutil/log.h>
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
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
        AVCodecContext* ctx =  avcodec_alloc_context3(codec);
        if(!ctx) {
            av_log(NULL,AV_LOG_ERROR,"avcodec_alloc_context3 err");
            throw -10003;
        }

        //4.设置编码器参数
        ctx->width = 640;
        ctx->height = 480;
        ctx->bit_rate = 500*1000; //设置码率

        ctx->time_base = (AVRational){1,25}; // 时间基 1 / 25
        ctx->framerate = (AVRational){25,1}; // 帧率 25 / 1
        ctx->gop_size = 10;  // 一组帧的大小(每10帧编成一组)
        ctx->max_b_frames = 1; //一组最多包含多少B帧，一般不超过3
        ctx->pix_fmt = AV_PIX_FMT_YUV420P; // 数据源类型
        if(codec->id == AV_CODEC_ID_H264) { //如果编码器是h264，可以设置私有参数，存常见的是preset

            //设置附加值（"preset","slow" key,value）,设置slow变啊清晰度会高一些。
            // 第四个参数是什么意思,此处是乱设的.
            av_opt_set(ctx->priv_data,"preset","slow",AV_OPT_SEARCH_CHILDREN);  //第四个参数怎么设置？

        }


        //5.编码器 解码器 上下文绑定到一起
        //6.创建输出文件
        //7.创建AVFrame
        //8.创建AVPacket
        //9.生成视频内容
        //10.编码
    } catch (int err) {

    }


}