
#include "00_draw_triangle.h"

/**
 * main
 */
int draw_triangle(GLFWwindow *window) {
    if (!window) {
        std::cout << "无法初始化" << std::endl;
        return -1;
    }

    float halfH = sqrtf(3) / 2 / 2;
    float vertexData[] = {
        0.0f,  halfH,  0.0f, 1.0f, 1.0f, 0.0f,
        0.5f,  -halfH, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -halfH, 0.0f, 1.0f, 0.0f, 1.0f,
    };

    // 缓冲对象
    GLuint VBO;
    glGenBuffers(1, &VBO);  // 生成缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // 绑定缓冲对象
    // 设置缓冲内存，并知道绘画模式
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    string shaderDir = string("/Users/haiyoucuv/Documents/OpenGl/TestOpenGL/TestOpenGL/TestOpenGL/shader/");
    Shader *shader = new Shader(shaderDir + "triangle_vShader.glsl",
                                shaderDir + "triangle_fShader.glsl");

    shader->use();

    // 设定绘画模式为线框模式
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // int u_ourColor = glGetUniformLocation(program, "u_ourColor");

    // 建立主循环
    // glfwWindowShouldClose会检查窗口是否需要退出，如果需要退出则结束主循环退出程序
    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            std::cout << "按下了\"Esc\"退出" << std::endl;
            glfwSetWindowShouldClose(window, true);
        }

        // 清屏
        glad_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glad_glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float value = (sin(timeValue) / 2.0f) + 0.5f;
        shader->setFloat("u_ourColor", value);

        // 绘制顶点
        glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

        glfwSwapBuffers(window); // 交换颜色缓冲（双缓冲的交换）（绘制）
        glfwPollEvents();        // 检查事件的触发，如键盘输入、鼠标移动
    }

    glfwTerminate();             // 结束主循环，释放资源
    return 0;
}
