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
    int idx = 0;
    // 打开多媒体文件
    // src 支持本地 和 远端
    // AVInputFormat 指定多媒体文件格式，如果不指定按后缀读取，如果对应不上会发生错误。
    // AVDictionary key,value值，设置特殊选项
    // return <0 错误  >0成功

    if((ret = avformat_open_input(&pFMtCxt,src,NULL,NULL)) < 0) {
        av_log(NULL,AV_LOG_ERROR,"avformat_open_input %s\n",av_err2str(ret));
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
        AVStream* inputSteam = pFMtCxt->streams[idx];
        avcodec_parameters_copy(outStream->codecpar,inputSteam->codecpar);
        // 设置成0  更具多媒体文件自动适配 编解码器，除非很了解，建议设置成0.
        outStream-> codecpar->codec_tag = 0;



    } catch(int errRet) {
        if(!pFMtCxt) {
            avformat_close_input(&pFMtCxt);
            oFMtCxt = NULL;
        }
    }

    return ret;
}
