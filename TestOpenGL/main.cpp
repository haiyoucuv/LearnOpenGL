
#include <glad.h>
#include <glfw3.h>

#include <iostream>
#include <math.h>
#include <string>
#include <zconf.h>

#include "Shader.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

GLFWwindow *init();    // 初始化

// 定义窗口大小
#define SCR_WIDTH  800
#define SCR_HEIGHT 800

#include "stb_image.h"


string PROJECT_DIR = "/Users/haiyoucuv/Documents/OpenGl/TestOpenGL/TestOpenGL/TestOpenGL/";

/**
 * main
 */
int main() {

    // 初始化并创建窗口
    GLFWwindow *window = init();
    if (!window) {
        std::cout << "无法初始化" << std::endl;
        return -1;
    }

    // 定义顶点数据
    // float vertexData[] = {
    //     -0.5f, 0.5f, 0.0f,
    //     0.5f, 0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f,
    //     -0.5f, -0.5f, 0.0f,
    // };


    /**
     *          (0.5,1)
     * (0,1) -------------- (1,1)
     *       |            |
     *       |    图片    |
     *       |            |
     * (0,0) -------------- (1,0)
     *          (0.5,0)
     */
    float texCoords[] = {
        0.0f, 0.0f, // 左下角
        1.0f, 0.0f, // 右下角
        0.5f, 1.0f  // 上中
    };

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
    int w, h, channels; // 宽，高，通道数
    unsigned char *data = stbi_load((PROJECT_DIR + "image/avater.jpeg").c_str(), &w, &h, &channels, 0);


    // 创建一个纹理
    GLuint texture;
    glGenTextures(1, &texture);

    // 绑定纹理
    glActiveTexture(GL_TEXTURE0);   // 激活纹理单元
    glBindTexture(GL_TEXTURE_2D, texture);


    // 填充纹理数据
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // 已经填充了可以被释放
    stbi_image_free(data);

    // 纹理uv   ------ 位置 ------   - 纹理坐标 -
    //          0.0f, 0.5f, 0.0f,   1.0f, 1.0f
    float vertexData[] = {
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, // 左上
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // 右上
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f,    // 右下
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,   // 左下
    };

    // float halfH = sqrtf(3) / 2 / 2;
    // float vertexData[] = {
    //     0.0f, halfH, 0.0f, 1.0f, 1.0f, 0.0f,
    //     0.5f, -halfH, 0.0f, 0.0f, 1.0f, 1.0f,
    //     -0.5f, -halfH, 0.0f, 1.0f, 0.0f, 1.0f,
    // };


    // 缓冲对象
    GLuint VBO;
    glGenBuffers(1, &VBO);  // 生成缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // 绑定缓冲对象
    // 设置缓冲内存，并知道绘画模式
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);

    Shader *shader = new Shader(PROJECT_DIR + "shader/" + "texture_vShader.glsl",
        PROJECT_DIR + "shader/" + "texture_fShader.glsl");

    shader->use();

    // 设定绘画模式为线框模式
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // 建立主循环
    // glfwWindowShouldClose会检查窗口是否需要退出，如果需要退出则结束主循环退出程序
    while (!glfwWindowShouldClose(window)) {

        processInput(window);

        // 清屏
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 绘制顶点
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glfwSwapBuffers(window); // 交换颜色缓冲（双缓冲的交换）（绘制）
        glfwPollEvents();        // 检查事件的触发，如键盘输入、鼠标移动
    }

    glfwTerminate();             // 结束主循环，释放资源
    return 0;
}

/**
 * 初始化并创建窗口
 * @return 窗口
 */
GLFWwindow *init() {
    // 初始化glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);      // 指定OpenGL配置文件为核心版本

    // 如果在苹果设备上则需要设置窗口的上下文是OpenGL前向兼容的上下文
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // 创建窗口
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello OpenGL", nullptr, nullptr);
    if (window == NULL) {
        std::cout << "无法创建glfw窗口" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    // 通知GLFW将我们窗口的上下文设置为当前线程的主上下文了
    glfwMakeContextCurrent(window);

    // 初始化glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "无法初始化glad" << std::endl;
        return nullptr;
    }

    // 注册当窗口大小改变时的回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window; // 返回窗口

}


/**
 * 检查键盘
 * @param window
 */
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        std::cout << "按下了\"Esc\"退出" << std::endl;
        glfwSetWindowShouldClose(window, true);
    }
}

/**
 * 窗口大小改变时的回调函数
 * @param window
 * @param width
 * @param height
 */
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    std::cout << "窗口大小改变:" << width << "×" << height << std::endl;
    glViewport(0, 0, width, height);
}
