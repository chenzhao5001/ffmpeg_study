cmake_minimum_required(VERSION 3.18.1)
project("hehe")
SET(TARGET "hehe")

add_library(
        hehe
        SHARED
        foo.cpp
        foo.h)

# 对hello_static的重名为hello
#SET_TARGET_PROPERTIES(hehe PROPERTIES  OUTPUT_NAME "hehe")
## cmake 在构建一个新的target 时，会尝试清理掉其他使用这个名字的库，如果没有清理还是会只会构建一个动态库，不会构建出静态库
#SET_TARGET_PROPERTIES(hehe PROPERTIES CLEAN_DIRECT_OUTPUT 1)


SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../output")
SET(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../output")



