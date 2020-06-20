//
//  05_camera_class.cpp
//  TestOpenGL
//
//  Created by 还有醋v on 2020/6/20.
//  Copyright © 2020 还有醋v. All rights reserved.
//

#include "05_camera_class.hpp"

Camera *camera5 = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), 45.0f, winWidth / winHeight, 0.1f, 100.0f);

int cameraClass(GLFWwindow *window) {

    if (!window) {
        cout << "无法初始化" << endl;
        return -1;
    }

    // 设置纹理环绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // 设置渐远纹理过滤方式
    glTexParameteri(GL_TEXTURE, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 设定绘画模式为线框模式
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 开启深度检测
    glEnable(GL_DEPTH_TEST);

    // 设置清屏颜色
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // 加载一个图片
    stbi_set_flip_vertically_on_load(true);
    int w, h, channels; // 宽，高，通道数
    unsigned char *data = stbi_load((PROJECT_DIR + "image/avater.jpeg").c_str(), &w, &h, &channels, 0);

    // 创建一个纹理
    GLuint texture;
    glGenTextures(1, &texture);

    // 绑定纹理
    glActiveTexture(GL_TEXTURE0);                            // 激活纹理单元
    glBindTexture(GL_TEXTURE_2D, texture);

    // 填充纹理数据
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // 已经填充了可以被释放
    stbi_image_free(data);

    glm::vec3 cubePositions[] = {
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    // 缓冲对象
    GLuint VBO;
    glGenBuffers(1, &VBO);                             // 生成缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                // 绑定缓冲对象

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    Shader *shader = new Shader(
        SHADER_DIR + "04_camera.vert",
        SHADER_DIR + "04_camera.frag"
    );

    shader->use();

    // 设置缓冲内存，并知道绘画模式
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexUVData), cubeVertexUVData, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    GLint u_model = shader->getUniformLocation("u_model");
    GLint u_view = shader->getUniformLocation("u_view");
    GLint u_projection = shader->getUniformLocation("u_projection");

    float lastT = glfwGetTime();
    float dt = 0.0f;
    // 建立主循环
    // glfwWindowShouldClose会检查窗口是否需要退出，如果需要退出则结束主循环退出程序
    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            std::cout << "按下了\"Esc\"退出" << std::endl;
            glfwSetWindowShouldClose(window, true);
        }

        float currentT = glfwGetTime();
        dt = currentT - lastT;
        lastT = currentT;

        // 清屏
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0; i < sizeof(cubePositions) / sizeof(glm::vec3); i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            // float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(50.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::rotate(model, (float) glfwGetTime() * glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, (float) glfwGetTime() * glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, (float) glfwGetTime() * glm::radians(20.0f), glm::vec3(0.0f, 0.0f, 1.0f));

            glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, sizeof(cubeVertexUVData) / sizeof(float) / 5);
        }

        camera5->update(dt);

        // camera5->lookAt(camera5->front);

        processInput(window, dt);

        glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(camera5->view));

        glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(camera5->projection));

        glfwSwapBuffers(window);                          // 交换颜色缓冲（双缓冲的交换）（绘制）
        glfwPollEvents();                                 // 检查事件的触发，如键盘输入、鼠标移动
    }

    glfwTerminate();                                      // 结束主循环，释放资源
    return 0;
}

void processInput(GLFWwindow *window, float dt) {
    float cameraSpeed = 0.05f;  // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera5->position += cameraSpeed * camera5->front;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera5->position -= cameraSpeed * camera5->front;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera5->position -= glm::normalize(glm::cross(camera5->front, camera5->worldUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera5->position += glm::normalize(glm::cross(camera5->front, camera5->worldUp)) * cameraSpeed;
    }
}

float lastX = 400, lastY = 400;
bool firstMouse = true;

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera5->yaw += xoffset;
    camera5->pitch += yoffset;

    if (camera5->pitch > 89.0f) {
        camera5->pitch = 89.0f;
    }
    if (camera5->pitch < -89.0f) {
        camera5->pitch = -89.0f;
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    if (camera5->fov >= 1.0f && camera5->fov <= 45.0f) {
        camera5->fov -= yoffset;
    }
    if (camera5->fov <= 1.0f) {
        camera5->fov = 1.0f;
    }

    if (camera5->fov >= 45.0f) {
        camera5->fov = 45.0f;
    }
}
