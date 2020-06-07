//
//  02_transformation.cpp
//  TestOpenGL
//
//  Created by 还有醋v on 2020/6/7.
//  Copyright © 2020 还有醋v. All rights reserved.
//

#include "02_transformation.hpp"

int transformation(GLFWwindow *window) {
    string PROJECT_DIR = "/Users/haiyoucuv/Documents/OpenGl/TestOpenGL/TestOpenGL/TestOpenGL/";

    if (!window) {
        std::cout << "无法初始化" << std::endl;
        return -1;
    }

    // 设置纹理环绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // 设置方法缩小时的纹理过滤方式
    // glTexParameteri(GL_TEXTURE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // 设置渐远纹理过滤方式
    glTexParameteri(GL_TEXTURE, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 加载一个图片
    //	stbi_set_flip_vertically_on_load(true);
    int w, h, channels;              // 宽，高，通道数
    unsigned char *data = stbi_load((PROJECT_DIR + "image/avater.jpeg").c_str(), &w, &h, &channels, 0);

    // 创建一个纹理
    GLuint texture;
    glGenTextures(1, &texture);

    // 绑定纹理
    glActiveTexture(GL_TEXTURE0);                // 激活纹理单元
    glBindTexture(GL_TEXTURE_2D, texture);

    // 填充纹理数据
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // 已经填充了可以被释放
    stbi_image_free(data);

    /**
            *          (0.5,1)
            * (0,1) -------------- (1,1)
            *       |            |
            *       |    图片    |
            *       |            |
            * (0,0) -------------- (1,0)
            *          (0.5,0)
            */

    // 纹理uv   ------ 位置 ------   - 纹理坐标 -
    //          0.0f, 0.5f, 0.0f,   1.0f, 1.0f
    float vertexData[] = {
        -0.5f, 0.5f,   0.0f,   0.0f, 0.0f, // 左上
        0.5f,  0.5f,   0.0f,   1.0f, 0.0f, // 右上
        0.5f,  -0.5f,  0.0f,   1.0f, 1.0f, // 右下
        -0.5f, -0.5f,  0.0f,   0.0f, 1.0f, // 左下
    };

    // 缓冲对象
    GLuint VBO;
    glGenBuffers(1, &VBO);                 // 生成缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);    // 绑定缓冲对象
    // 设置缓冲内存，并知道绘画模式
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);

    Shader *shader = new Shader(PROJECT_DIR + "shader/" + "02_transformation_vShader.glsl",
                                PROJECT_DIR + "shader/" + "02_transformation_fShader.glsl");

    shader->use();

    // 设定绘画模式为线框模式
    //	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // 生成单位矩阵
    glm::mat4 trans = glm::mat4(1.0f);

    // 移动画矩阵
//    trans = glm::translate(trans, glm::vec3(0.1f, 0.0f, 0.0f));

    // 旋转
//    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));

    // 缩放
    trans = glm::scale(trans, glm::vec3(2, 2, 2));
    GLuint u_transform = glGetUniformLocation(shader->id, "u_transform");
    glUniformMatrix4fv(u_transform, 1, GL_TRUE, glm::value_ptr(trans));

    // 建立主循环
    // glfwWindowShouldClose会检查窗口是否需要退出，如果需要退出则结束主循环退出程序
    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            std::cout << "按下了\"Esc\"退出" << std::endl;
            glfwSetWindowShouldClose(window, true);
        }

        // 清屏
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(u_transform, 1, GL_TRUE, glm::value_ptr(trans));

        // 绘制顶点
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glfwSwapBuffers(window);              // 交换颜色缓冲（双缓冲的交换）（绘制）
        glfwPollEvents();                     // 检查事件的触发，如键盘输入、鼠标移动
    }

    glfwTerminate();                          // 结束主循环，释放资源
    return 0;
}
