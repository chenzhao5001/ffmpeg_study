//
// Created by chenz on 2022/11/11.
//

#include <iostream>
#include "MediaControl.h"

MediaControl::MediaControl() {}

MediaControl::~MediaControl() {
    if(avFrame) {
        av_frame_free(&avFrame);
    }
    if(avPacket) {
        av_packet_free(&avPacket);
    }
    if(decCtx) {
        avcodec_free_context(&decCtx);
    }
    if(fmt) {
        avformat_close_input(&fmt);
//        avformat_free_context(fmt);
    }
}

void MediaControl::setWindow(WindowCell windowCell) {
    this->windowCell = windowCell;
}


MediaRect MediaControl::openFmt(std::string path) {
    int ret = avformat_open_input(&this->fmt,path.c_str(),NULL,NULL);
    std::cout << "avformat_open_input call: ret = " << ret << std::endl;
    // 对流信息提取
    ret = avformat_find_stream_info(this->fmt,NULL);
    std::cout << "avformat_find_stream_info: ret = " << ret << std::endl;

    this->idx = av_find_best_stream(this->fmt,AVMEDIA_TYPE_VIDEO,-1,-1,NULL,0);
    std::cout << "av_find_best_stream: ret = " << this->idx << std::endl;

    this->inStream = this->fmt->streams[this->idx];
    this->dec = avcodec_find_decoder(this->inStream->codecpar->codec_id);
    // 创建解码器上下文
    this->decCtx =  avcodec_alloc_context3(this->dec);

    // 从视频流中拷贝解码器参数岛解码器上下文
    ret = avcodec_parameters_to_context(this->decCtx,this->inStream->codecpar);
    std::cout << "avcodec_parameters_to_context: ret = " << ret << std::endl;

    // 绑定解码器 和 解码器上下文
    ret = avcodec_open2(this->decCtx,this->dec, nullptr);
    std::cout << "avcodec_open2: ret = " << ret << std::endl;

    avPacket = av_packet_alloc();
    avFrame= av_frame_alloc();
    VideoState videoState;

    videoState.avCtx = decCtx;
    videoState.avPkt = avPacket;
    videoState.avFrame = avFrame;
    videoState.texture = windowCell.pTexture;

//    ret = av_read_frame(fmt,avPacket);

    // 从多媒体文件中读取数据
    while (av_read_frame(fmt,avPacket) >= 0) {
        if(avPacket->stream_index == idx) {
            decode(videoState);
//            this->dec(this->decCtx,)
        }

        //每次调用要减引用基数，否则有内存泄露
        av_packet_unref(avPacket);
    }

    //清楚缓冲区
    videoState.avPkt = nullptr;
    decode(videoState);


    int width = this->decCtx->width;
    int height = this->decCtx->height;
    return MediaRect{width,height};
}

int MediaControl::decode(VideoState& videoState) {
    int ret = -1;
    char buf[1024];
    ret = avcodec_send_packet(videoState.avCtx,videoState.avPkt);
//    std::cout << "avcodec_send_packet called,ret = " << ret << std::endl;

    while (ret >=0) {
        // 解码成功后 videoState.avFrame 里面就有解码后的frame
        ret = avcodec_receive_frame(videoState.avCtx,videoState.avFrame);
        if(ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
            return 0;  // 外层继续读取，送进了新的
        } else if(ret < 0) {
            return -1; // 错误
        }
        render(videoState);
    }
    return ret;
}

void MediaControl::render(VideoState& videoState) {
    // rect 设置成null，整个纹理进行更新
    // 渲染纹理
//    std::cout << videoState.avFrame->data[0] << videoState.avFrame->data[0] << videoState.avFrame->data[0];
    SDL_UpdateYUVTexture(videoState.texture,
                         nullptr,
                         videoState.avFrame->data[0], videoState.avFrame->linesize[0], // yvu 中的Y
                         videoState.avFrame->data[1], videoState.avFrame->linesize[1], // U
                         videoState.avFrame->data[2], videoState.avFrame->linesize[2]  // V
                         );
    SDL_RenderClear(windowCell.pRender);
    // null1 整个纹理  null2 整个窗口
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 500;
    rect.h = 500;

    SDL_RenderCopy(windowCell.pRender, videoState.texture, nullptr, nullptr);
    SDL_RenderPresent(windowCell.pRender);
    std::cout << "test" << std::endl;
}
