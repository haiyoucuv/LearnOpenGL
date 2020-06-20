//
//  06_light.cpp
//  TestOpenGL
//
//  Created by 还有醋v on 2020/6/20.
//  Copyright © 2020 还有醋v. All rights reserved.
//

#include "07_baseLight.hpp"

Camera *camera7 = new Camera(glm::vec3(0.0f, 0.0f, 8.0f), 45.0f, winWidth / winHeight, 0.1f, 100.0f);
// 灯光位置
glm::vec3 lightPos = glm::vec3(1.2f, 0.8f, 1.5);

int baseLight(GLFWwindow *window) {

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
    glfwSetCursorPosCallback(window, mouse_callback7);
    glfwSetScrollCallback(window, scroll_callback7);

    // 缓冲对象
    GLuint VBO;
    glGenBuffers(1, &VBO);  // 创建缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // 绑定缓冲对象
    // 输入顶点数据，设置缓冲内存，并设置绘画模式
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexNormalData), cubeVertexNormalData, GL_STATIC_DRAW);

    // 顶点对象
    GLuint cubeVAO;
    glGenVertexArrays(1, &cubeVAO); // 创建顶点对象
    glBindVertexArray(cubeVAO); // 绑定顶点对象

    // 创建 Cube Shader
    Shader *cubeShader = new Shader(
        PROJECT_DIR + "case/07_baseLight/07_baseLight.vert",
        PROJECT_DIR + "case/07_baseLight/07_baseLight.frag"
    );
    cubeShader->use();
    cubeShader->setVec3("u_lightPos", lightPos);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 灯光
    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // 灯光Shader
    Shader *lightShader = new Shader(
        PROJECT_DIR + "case/07_baseLight/07_baseLight.vert",
        PROJECT_DIR + "case/07_baseLight/07_baseLight_light.frag"
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

        processInput7(window, dt);

        // 清屏
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera7->update(dt);

        // 方块
        cubeShader->use();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float) glfwGetTime() * glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, (float) glfwGetTime() * glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, (float) glfwGetTime() * glm::radians(20.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        cubeShader->setMat4("u_model", model);
        cubeShader->setMat4("u_view", camera7->view);
        cubeShader->setMat4("u_projection", camera7->projection);

        cubeShader->setVec3("u_objectColor", 1.0f, 0.1f, 0.1f);
        cubeShader->setVec3("u_lightColor", 1.0f, 1.0f, 1.0f);
        cubeShader->setVec3("u_viewPos", camera7->position);

        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(cubeVertexNormalData) / sizeof(float) / 6);

        // 灯光
        lightShader->use();
        lightShader->setMat4("u_projection", camera7->projection);
        lightShader->setMat4("u_view", camera7->view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.1f));
        lightShader->setMat4("u_model", model);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(cubeVertexNormalData) / sizeof(float) / 6);

        glfwSwapBuffers(window);    // 交换颜色缓冲（双缓冲的交换）（绘制）
        glfwPollEvents();   // 检查事件的触发，如键盘输入、鼠标移动
    }

    glfwTerminate();    // 结束主循环，释放资源
    return 0;

}

void processInput7(GLFWwindow *window, float dt) {
    float cameraSpeed = 0.1f;  // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera7->position += cameraSpeed * camera7->front;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera7->position -= cameraSpeed * camera7->front;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera7->position -= glm::normalize(glm::cross(camera7->front, camera7->worldUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera7->position += glm::normalize(glm::cross(camera7->front, camera7->worldUp)) * cameraSpeed;
    }
}


float lastX7 = 400, lastY7 = 400;
bool firstMouse7 = true;

void mouse_callback7(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse7) {
        lastX7 = xpos;
        lastY7 = ypos;
        firstMouse7 = false;
    }

    float xoffset = xpos - lastX7;
    float yoffset = lastY7 - ypos;
    lastX7 = xpos;
    lastY7 = ypos;

    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera7->yaw += xoffset;
    camera7->pitch += yoffset;

    if (camera7->pitch > 89.0f) {
        camera7->pitch = 89.0f;
    }
    if (camera7->pitch < -89.0f) {
        camera7->pitch = -89.0f;
    }
}

void scroll_callback7(GLFWwindow *window, double xoffset, double yoffset) {
    if (camera7->fov >= 1.0f && camera7->fov <= 45.0f) {
        camera7->fov -= yoffset;
    }
    if (camera7->fov <= 1.0f) {
        camera7->fov = 1.0f;
    }

    if (camera7->fov >= 45.0f) {
        camera7->fov = 45.0f;
    }
}