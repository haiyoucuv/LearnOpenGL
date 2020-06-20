// //
// //  04_camera.cpp
// //  TestOpenGL
// //
// //  Created by 还有醋v on 2020/6/9.
// //  Copyright © 2020 还有醋v. All rights reserved.
// //
//
// #include "04_camera.hpp"
//
// float yaw = -90.0f;
// float pitch = 0.0f;
// float fov = 45.0f;
// // camera5
// glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
// glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
// glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//
// int camera5(GLFWwindow *window) {
//
//     if (!window) {
//         std::cout << "无法初始化" << std::endl;
//         return -1;
//     }
//
//     // 设置纹理环绕方式
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//     // 设置渐远纹理过滤方式
//     glTexParameteri(GL_TEXTURE, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//     glTexParameteri(GL_TEXTURE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//     // 加载一个图片
//     stbi_set_flip_vertically_on_load(true);
//     int w, h, channels; // 宽，高，通道数
//     unsigned char *data = stbi_load((PROJECT_DIR + "image/avater.jpeg").c_str(), &w, &h, &channels, 0);
//
//     // 创建一个纹理
//     GLuint texture;
//     glGenTextures(1, &texture);
//
//     // 绑定纹理
//     glActiveTexture(GL_TEXTURE0);                            // 激活纹理单元
//     glBindTexture(GL_TEXTURE_2D, texture);
//
//     // 填充纹理数据
//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//     glGenerateMipmap(GL_TEXTURE_2D);
//
//     // 已经填充了可以被释放
//     stbi_image_free(data);
//
//     // 纹理uv   ------ 位置 ------   - 纹理坐标 -
//     float cubeVertexUVData[] = {
//         // Front face
//         -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
//         0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
//         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//         -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
//         -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
//
//         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//         0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
//         0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
//         -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
//         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//
//         -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//         -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//         -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//
//         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//         0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//         0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//
//         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
//         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//
//         -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
//         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//         -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
//         -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
//     };
//
//     glm::vec3 cubePositions[] = {
//         glm::vec3(2.0f, 5.0f, -15.0f),
//         glm::vec3(-1.5f, -2.2f, -2.5f),
//         glm::vec3(-3.8f, -2.0f, -12.3f),
//         glm::vec3(2.4f, -0.4f, -3.5f),
//         glm::vec3(-1.7f, 3.0f, -7.5f),
//         glm::vec3(1.3f, -2.0f, -2.5f),
//         glm::vec3(1.5f, 2.0f, -2.5f),
//         glm::vec3(1.5f, 0.2f, -1.5f),
//         glm::vec3(-1.3f, 1.0f, -1.5f)
//     };
//
//     // 缓冲对象
//     GLuint VBO;
//     glGenBuffers(1, &VBO);                             // 生成缓冲对象
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);                // 绑定缓冲对象
//     // 设置缓冲内存，并知道绘画模式
//     glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexUVData), cubeVertexUVData, GL_STATIC_DRAW);
//
//     GLuint VAO;
//     glGenVertexArrays(1, &VAO);
//     glBindTexture(GL_TEXTURE_2D, texture);
//     glBindVertexArray(VAO);
//
//     Shader *shader = new Shader(PROJECT_DIR + "shader/" + "04_camera.vert",
//         PROJECT_DIR + "shader/" + "04_camera.frag");
//
//     shader->use();
//
//     // 设定绘画模式为线框模式
//     // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
//     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
//
//     glEnableVertexAttribArray(0);
//     glEnableVertexAttribArray(1);
//
//     // 模型矩阵
//     // glm::mat4 model = glm::mat4(1.0f);
//
//     // 投影矩阵
//     glm::mat4 projection = glm::mat4(1.0f);
//     projection = glm::perspective(glm::radians(45.0f), winWidth / winHeight, 0.1f, 100.0f);
//
//     GLint u_model = glGetUniformLocation(shader->id, "u_model");
//     GLint u_view = glGetUniformLocation(shader->id, "u_view");
//     GLint u_projection = glGetUniformLocation(shader->id, "u_projection");
//
//     glEnable(GL_DEPTH_TEST);
//
//     glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);   // 相机指向的位置
//
//     // 相机位置 - 相机指向的位置 得到方向向量 z
//     glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
//
//     glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // 一个标准的向上向量
//
//     // 使用标准上向量和方向向量叉乘得到向右向量 x
//     glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
//
//     // 使用方向向量和右向量叉乘得到向上向量 y
//     cameraUp = glm::cross(cameraDirection, cameraRight);
//
//     // 观察矩阵
//     // glm::mat4 view = glm::mat4(1.0f);
//     // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
//
//     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//     glfwSetCursorPosCallback(window, mouse_callback);
//     glfwSetScrollCallback(window, scroll_callback);
//
//     float lastT = glfwGetTime();
//     float dt = 0.0f;
//     // 建立主循环
//     // glfwWindowShouldClose会检查窗口是否需要退出，如果需要退出则结束主循环退出程序
//     while (!glfwWindowShouldClose(window)) {
//         if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//             std::cout << "按下了\"Esc\"退出" << std::endl;
//             glfwSetWindowShouldClose(window, true);
//         }
//
//         // 清屏
//         glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//         // glClear(GL_COLOR_BUFFER_BIT);
//
//         for (int i = 0; i < sizeof(cubePositions) / sizeof(glm::vec3); i++) {
//             glm::mat4 model = glm::mat4(1.0f);
//             model = glm::translate(model, cubePositions[i]);
//             // float angle = 20.0f * i;
//             model = glm::rotate(model, glm::radians(50.0f), glm::vec3(1.0f, 1.0f, 1.0f));
//             model = glm::rotate(model, (float) glfwGetTime() * glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//             model = glm::rotate(model, (float) glfwGetTime() * glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//             model = glm::rotate(model, (float) glfwGetTime() * glm::radians(20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//
//             glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));
//
//             glDrawArrays(GL_TRIANGLES, 0, sizeof(cubeVertexUVData) / sizeof(float) / 5);
//         }
//
//         float currentT = glfwGetTime();
//         dt = currentT - lastT;
//         lastT = currentT;
//
//         glm::mat4 view = glm::lookAt(
//             cameraPos,
//             cameraPos + cameraFront,
//             cameraUp
//         );
//
//         processInput(window, dt, &cameraPos, &cameraFront, &cameraUp);
//
//         glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view));
//
//         projection = glm::perspective(glm::radians(fov), 800.0f / 800.0f, 0.1f, 100.0f);
//         glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection));
//
//         glfwSwapBuffers(window);                          // 交换颜色缓冲（双缓冲的交换）（绘制）
//         glfwPollEvents();                                 // 检查事件的触发，如键盘输入、鼠标移动
//     }
//
//     glfwTerminate();                                      // 结束主循环，释放资源
//     return 0;
// }
//
// void processInput(GLFWwindow *window, float dt, glm::vec3 *cameraPos, glm::vec3 *cameraFront, glm::vec3 *cameraUp) {
//     float cameraSpeed = 0.05f;  // adjust accordingly
//     if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//         *cameraPos += cameraSpeed * *cameraFront;
//     }
//     if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//         *cameraPos -= cameraSpeed * *cameraFront;
//     }
//     if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//         *cameraPos -= glm::normalize(glm::cross(*cameraFront, *cameraUp)) * cameraSpeed;
//     }
//     if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//         *cameraPos += glm::normalize(glm::cross(*cameraFront, *cameraUp)) * cameraSpeed;
//     }
// }
//
// float lastX = 400, lastY = 400;
// bool firstMouse = true;
//
// void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
//     if (firstMouse) {
//         lastX = xpos;
//         lastY = ypos;
//         firstMouse = false;
//     }
//
//     float xoffset = xpos - lastX;
//     float yoffset = lastY - ypos;
//     lastX = xpos;
//     lastY = ypos;
//
//     float sensitivity = 0.05;
//     xoffset *= sensitivity;
//     yoffset *= sensitivity;
//
//     yaw += xoffset;
//     pitch += yoffset;
//
//     if (pitch > 89.0f) {
//         pitch = 89.0f;
//     }
//     if (pitch < -89.0f) {
//         pitch = -89.0f;
//     }
//
//     glm::vec3 front;
//     front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//     front.y = sin(glm::radians(pitch));
//     front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//
//     cameraFront = glm::normalize(front);
// }
//
// void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
//     if (fov >= 1.0f && fov <= 45.0f) {
//         fov -= yoffset;
//     }
//     if (fov <= 1.0f) {
//         fov = 1.0f;
//     }
//
//     if (fov >= 45.0f) {
//         fov = 45.0f;
//     }
// }
