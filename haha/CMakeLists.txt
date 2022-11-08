cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

project("haha")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

SET(TARGET "haha")

add_library( # Sets the name of the library.
        haha
        STATIC
        goo.cpp
        goo.h)

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")
SET(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")


