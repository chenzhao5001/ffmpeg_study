cmake_minimum_required(VERSION 3.23)
project(ffmpeg_test)
set(CMAKE_CXX_STANDARD 11)



ADD_SUBDIRECTORY(haha) #如果不把子目录加入，会报错。(引入包含CMakeList的目录)
ADD_SUBDIRECTORY(hehe)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/haha") #要到haha目录，否则找不到
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/hehe")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/thirdLib/ffmpeg/include")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/thirdLib/sdl/include")
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/thirdLib/glfw/include")


link_directories(${PROJECT_SOURCE_DIR}/thirdLib/ffmpeg/lib)
link_directories(${PROJECT_SOURCE_DIR}/thirdLib/sdl/lib)
link_directories(${PROJECT_SOURCE_DIR}/thirdLib/glfw/lib)

#这里我调了很久，add_executable 要在 link_directories后面
add_executable(ffmpeg_test
        main.cpp
        util/io_test.cpp
        util/io_test.h
        util/codec.cpp
        util/codec.h
        util/extra_audio.cpp
        util/extra_video.cpp

        player/newPlay.cpp
        player/newPlay.h
        player/openglPlayer.cpp
        player/openglPlayer.h

        window/MediaControl.cpp
        window/MediaControl.h
        window/PlayWindow.cpp
        window/PlayWindow.h)



target_link_libraries( # Specifies the target library.
        ffmpeg_test

        avformat-59.dll
        avcodec-59.dll
        avutil-57.dll

        SDL2.dll
        glfw3.a
        hehe
        haha)

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/output")
SET(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/output")
