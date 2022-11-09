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
    int ret = 0;
    AVFormatContext* pFMtCxt = NULL;
    AVFormatContext* oFMtCxt = NULL;
    AVPacket pkt;
    int idx = 0;
    // 打开多媒体文件
    // src 支持本地 和 远端
    // AVInputFormat 指定多媒体文件格式，如果不指定按后缀读取，如果对应不上会发生错误。
    // AVDictionary key,value值，设置特殊选项
    // return <0 错误  >0成功

    if((ret = avformat_open_input(&pFMtCxt,src,NULL,NULL)) < 0) {
        // 编译不通过 由于 c c++ 编译冲突
//        av_log(NULL,AV_LOG_ERROR,"avformat_open_input %s\n",av_err2str(ret));
        return ret;
    }

    try{
        //3.从多媒体文件中找到音频流

        //wanted_stream_nb 想要哪一路流，不知道可以设置-1
        //related_stream sdl相关，不知道可以设置-1（以后了解）
        //AVCodec **decoder_ret 指定解码器，不指定设置null
        // flags: none are currently defined
        idx = av_find_best_stream(pFMtCxt,AVMEDIA_TYPE_AUDIO,-1,-1,NULL,0);
        if(idx < 0) {
            av_log(pFMtCxt,AV_LOG_ERROR,"av_find_best_stream err ret = %d\n",idx);
            throw idx;
        }

        //4 打开目的文件的上下文
        oFMtCxt =  avformat_alloc_context();
        if(!oFMtCxt) {
            av_log(oFMtCxt,AV_LOG_ERROR,"avformat_alloc_context err \n");
            throw -10001;
        }
        // 通过此函数获取基本参数，减少设置参数的复杂度
        const AVOutputFormat* avOutputFormat = av_guess_format(NULL,dst,NULL);
        oFMtCxt->oformat = avOutputFormat;

        //6.设置输出音频参数
        // 为目标文件创音频流
        AVStream* outStream = avformat_new_stream(oFMtCxt,NULL);
        AVStream* inStream = pFMtCxt->streams[idx];
        avcodec_parameters_copy(outStream->codecpar,inStream->codecpar);
        // 设置成0  更具多媒体文件自动适配 编解码器，除非很了解，建议设置成0.
        outStream-> codecpar->codec_tag = 0;

        // 绑定目标文件
        // AVIOContext
        // flags 设置读写权限
        // AVIOInterruptCB 回调函数，此处不用
        // AVDictionary 私有协议设置，此处不用
        ret = avio_open2(&oFMtCxt->pb, dst,AVIO_FLAG_WRITE,NULL,NULL);
        if(ret < 0) {
            av_log(oFMtCxt,AV_LOG_ERROR,"avio_open2 err ret = %d",ret);
            throw ret;
        }
        //7 写多媒体文件到目的文件。
        ret = avformat_write_header(oFMtCxt,NULL);
        if(ret < 0) {
            av_log(oFMtCxt,AV_LOG_ERROR,"avformat_write_header err ret = %d",ret);
            throw ret;
        }

        //8 从源多媒体文件中读音频数据到目的文件

        //从多媒体文件中读取帧数据
        while (av_read_frame(pFMtCxt,&pkt) > 0) {

            //看读取的数据是否是预期的流数据
            if(pkt.stream_index == idx) {
                // pts dts 的概念是什么？
                // 参数1 原始pts,参数2 输入流的时间基 3输出流时间基本 4 设置近似值
                pkt.pts = av_rescale_q_rnd(pkt.pts,inStream->time_base,outStream->time_base,AV_ROUND_NEAR_INF);
                pkt.dts = pkt.pts;
                pkt.duration = av_rescale_q(pkt.duration,inStream->time_base,outStream->time_base);

                //只抽取了一路音频，这里设置成0
                pkt.stream_index = 0;
                // 相对位置？ 设置成-1，自己进行积算
                pkt.pos = -1;

                av_interleaved_write_frame(oFMtCxt,&pkt);
                //减少包的引用计数，相当于包被释放了，子读取pkt又是个新包
                av_packet_unref(&pkt);
            }

        }
        //9 写多媒体文件尾到目的文件
        av_write_trailer(oFMtCxt);

    } catch(int errRet) {

    }

    //10 释放申请的资源。
    if(pFMtCxt) {
        avformat_close_input(&pFMtCxt);
        pFMtCxt = NULL;
    }

    if(oFMtCxt) {
        if(oFMtCxt->pb) {
            avio_close(oFMtCxt->pb);
        }
        avformat_close_input(&oFMtCxt);
        oFMtCxt = NULL;
    }

    return ret;
}
