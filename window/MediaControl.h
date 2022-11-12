//
// Created by chenz on 2022/11/11.
//

#ifndef FFMPEG_TEST_MEDIACONTROL_H
#define FFMPEG_TEST_MEDIACONTROL_H

extern "C" {
#include <libavutil/log.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavcodec/avcodec.h>

#include <SDL.h>
};

#include <string>
struct MediaRect {
    int width;
    int height;
};

struct VideoState {
    AVCodecContext* avCtx;
    AVPacket*       avPkt;
    AVFrame*        avFrame;
    SDL_Texture*    texture;
};

struct WindowCell{
    SDL_Window* pWindow = nullptr;
    SDL_Renderer* pRender = nullptr;
    SDL_Texture* pTexture =  nullptr;
};




class MediaControl {
public:
    MediaControl();
    ~MediaControl();
    void setWindow(WindowCell windowCell);
    MediaRect openFmt(std::string path);


private:
    WindowCell windowCell;

    AVFormatContext* fmt = nullptr;

    int idx = -1; //流id
    AVStream* inStream = nullptr; // 输入流

    // const 说明我们只是引用，不是我们创建的，不用释放
    const AVCodec* dec = nullptr;  //解码器
    AVCodecContext* decCtx = nullptr; // 解码器上下文

    AVPacket* avPacket = nullptr;
    AVFrame* avFrame = nullptr;

private:
    int decode(VideoState& videoState);
    void render(VideoState& videoState);
};


#endif //FFMPEG_TEST_MEDIACONTROL_H
