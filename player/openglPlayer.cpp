//
// Created by chenz on 2022/11/10.
//
#include <GLFW\glfw3.h>
#include "openglPlayer.h"

#include <iostream>
OpenGlPlayer::OpenGlPlayer() {

}

OpenGlPlayer::~OpenGlPlayer() {

}

void OpenGlPlayer::test() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
}