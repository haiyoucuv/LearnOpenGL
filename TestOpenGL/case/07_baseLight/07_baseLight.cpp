//
//  06_light.cpp
//  TestOpenGL
//
//  Created by 还有醋v on 2020/6/20.
//  Copyright © 2020 还有醋v. All rights reserved.
//

#include "06_light.hpp"

Camera *camera6 = new Camera(glm::vec3(0.0f, 0.0f, 8.0f), 45.0f, winWidth / winHeight, 0.1f, 100.0f);

int light(GLFWwindow *window) {

    if (!window) {
        cout << "无法初始化" << endl;
        return -1;
    }

    // 设定绘画模式
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 开启深度检测
    glEnable(GL_DEPTH_TEST);

    // 设置清屏颜色
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback6);
    glfwSetScrollCallback(window, scroll_callback6);

    // 缓冲对象
    GLuint VBO;
    glGenBuffers(1, &VBO);  // 创建缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // 绑定缓冲对象

    // 顶点对象
    GLuint cubeVAO;
    glGenVertexArrays(1, &cubeVAO); // 创建顶点对象
    glBindVertexArray(cubeVAO); // 绑定顶点对象

    // 创建 Cube Shader
    Shader *cubeShader = new Shader(
        shaderDir + "06_light.vert",
        shaderDir + "06_light.frag"
    );

    // 输入顶点数据，设置缓冲内存，并设置绘画模式
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexData), cubeVertexData, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // 灯光
    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // 灯光Shader
    Shader *lightShader = new Shader(
        shaderDir + "06_light.vert",
        shaderDir + "06_light_light.frag"
    );

    float lastT = glfwGetTime();
    float dt = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            cout << "按下了\"Esc\"退出" << endl;
            glfwSetWindowShouldClose(window, true);
        }

        float currentT = glfwGetTime();
        dt = currentT - lastT;
        lastT = currentT;

        processInput6(window, dt);

        // 清屏
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera6->update(dt);

        // 方块
        cubeShader->use();

        cubeShader->setVec3("u_objectColor", 0.5f, 0.5f, 0.5f);
        cubeShader->setVec3("u_lightColor", 1.0f, 1.0f, 1.0f);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float) glfwGetTime() * glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, (float) glfwGetTime() * glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, (float) glfwGetTime() * glm::radians(20.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        cubeShader->setMat4("u_model", model);
        cubeShader->setMat4("u_view", camera6->view);
        cubeShader->setMat4("u_projection", camera6->projection);

        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(cubeVertexData) / sizeof(float) / 5);

        // 灯光
        lightShader->use();
        lightShader->setMat4("u_projection", camera6->projection);
        lightShader->setMat4("u_view", camera6->view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.2f, 1.0f, 2.0f));
        model = glm::scale(model, glm::vec3(0.1f)); // a smaller cube
        lightShader->setMat4("u_model", model);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(cubeVertexData) / sizeof(float) / 5);

        glfwSwapBuffers(window);    // 交换颜色缓冲（双缓冲的交换）（绘制）
        glfwPollEvents();   // 检查事件的触发，如键盘输入、鼠标移动
    }

    glfwTerminate();    // 结束主循环，释放资源
    return 0;

}

void processInput6(GLFWwindow *window, float dt);

void processInput6(GLFWwindow *window, float dt) {
    float cameraSpeed = 0.05f;  // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera6->position += cameraSpeed * camera6->front;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera6->position -= cameraSpeed * camera6->front;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera6->position -= glm::normalize(glm::cross(camera6->front, camera6->worldUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera6->position += glm::normalize(glm::cross(camera6->front, camera6->worldUp)) * cameraSpeed;
    }
}


float lastX6 = 400, lastY6 = 400;
bool firstMouse6 = true;

void mouse_callback6(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse6) {
        lastX6 = xpos;
        lastY6 = ypos;
        firstMouse6 = false;
    }

    float xoffset = xpos - lastX6;
    float yoffset = lastY6 - ypos;
    lastX6 = xpos;
    lastY6 = ypos;

    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera6->yaw += xoffset;
    camera6->pitch += yoffset;

    if (camera6->pitch > 89.0f) {
        camera6->pitch = 89.0f;
    }
    if (camera6->pitch < -89.0f) {
        camera6->pitch = -89.0f;
    }
}

void scroll_callback6(GLFWwindow *window, double xoffset, double yoffset) {
    if (camera6->fov >= 1.0f && camera6->fov <= 45.0f) {
        camera6->fov -= yoffset;
    }
    if (camera6->fov <= 1.0f) {
        camera6->fov = 1.0f;
    }

    if (camera6->fov >= 45.0f) {
        camera6->fov = 45.0f;
    }
}