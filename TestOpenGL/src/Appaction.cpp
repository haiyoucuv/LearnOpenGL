//
//  Appaction.cpp
//  TestOpenGL
//
//  Created by 还有醋v on 2020/6/7.
//  Copyright © 2020 还有醋v. All rights reserved.
//

#include "Appaction.hpp"

Appaction::Appaction() {
	this->window = this->init(800, 800);
}

Appaction::~Appaction() {
}

/**
* 初始化并创建窗口
* @return 窗口
*/
GLFWwindow * Appaction::init(int width, int height) {
    // 初始化glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);                      // 指定OpenGL配置文件为核心版本

    // 如果在苹果设备上则需要设置窗口的上下文是OpenGL前向兼容的上下文
        #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif

    // 创建窗口
    GLFWwindow *window = glfwCreateWindow(width, height, "Hello OpenGL", nullptr, nullptr);
    if (window == NULL) {
        std::cout << "无法创建glfw窗口" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    // 通知GLFW将我们窗口的上下文设置为当前线程的主上下文了
    glfwMakeContextCurrent(window);

    // 初始化glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "无法初始化glad" << std::endl;
        return nullptr;
    }

    // 注册当窗口大小改变时的回调函数
    glfwSetFramebufferSizeCallback(window, Appaction::framebuffer_size_callback);

    return window;                 // 返回窗口
}

/**
* 窗口大小改变时的回调函数
* @param window
* @param width
* @param height
*/
void Appaction::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    std::cout << "窗口大小改变:" << width << "×" << height << std::endl;
    glViewport(0, 0, width, height);
}
