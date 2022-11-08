cmake_minimum_required(VERSION 3.18.1)
project("hehe")
SET(TARGET "hehe")

add_library(
        hehe
        SHARED
        foo.cpp
        foo.h)

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../output")
SET(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../output")



