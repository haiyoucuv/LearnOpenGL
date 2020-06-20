//
// Created by 还有醋v on 2020/5/31.
// Copyright (c) 2020 还有醋v. All rights reserved.
//

#include "Shader.h"

// Shader::Shader(const char *vertexPath, const char *fragmentPath) {
Shader::Shader(string vertexPath, string fragmentPath) {
    // 从文件中读取着色器源码
    string vertexCode, fragmentCode;

    ifstream vShaderFile, fShaderFile;

    // 设置使其可以抛出异常
    vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    try {
        // 打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        stringstream vShaderStream, fShaderStream;

        // 将读取文件的缓冲区加载到数据流中
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // 转换成string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        // 关闭文件处理器
        vShaderFile.close();
        fShaderFile.close();
    } catch (ifstream::failure e) {
        cout << "读取shader文件失败" << endl;
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    // 创建着色器程序并保存id
    this->id = createProgram(vShaderCode, fShaderCode);
}

Shader::~Shader() {
    this->id = 0;
}

void Shader::use() {
    glUseProgram(this->id);
}

void Shader::setVec3(const GLchar *name, glm::vec3 value) {
    // glUniform3f(glGetUniformLocation(this->id, name), value.x, value.y, value.z);
    this->setVec3(name, value.x, value.y, value.z);
}

void Shader::setVec3(const GLchar *name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(this->id, name), x, y, z);
}

void Shader::setMat4(const GLchar *name, glm::mat4 value) {
    glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GLFW_FALSE, glm::value_ptr(value));
}

GLint Shader::getUniformLocation(const GLchar *name) {
    return glGetUniformLocation(this->id, name);
}


void Shader::setBool(const string &name, bool value) const {
    glUniform1i(glGetUniformLocation(this->id, name.c_str()), (int) value);
}

void Shader::setInt(const string &name, int value) const {
    glUniform1i(glGetUniformLocation(this->id, name.c_str()), value);
}

void Shader::setFloat(const string &name, float value) const {
    glUniform1f(glGetUniformLocation(this->id, name.c_str()), value);
}


/**
 * 加载shader
 * @param shaderCode 源码
 * @param type 类型
 * @return
 */
GLuint Shader::createShader(const char *shaderCode, GLenum type) {
    GLuint shader = glCreateShader(type);
    // 设置着色器source并编译
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    // 检查着色器是否编译成功
    GLint success = this->checkError(shader, "SHADER");

    return success ? shader : 0;
}


/**
 * 创建着色器程序
 * @param vertexShaderSource 顶点着色器源码
 * @param fragmentShaderSource 片原着色器源码
 * @return
 */
GLuint Shader::createProgram(const char *vertexShaderCode, const char *fragmentShaderCode) {
    // 创建并加载着色器source
    GLuint vertexShader = this->createShader(vertexShaderCode, GL_VERTEX_SHADER);
    GLuint fragmentShader = this->createShader(fragmentShaderCode, GL_FRAGMENT_SHADER);
    if (vertexShader == -1 || fragmentShader == -1) {
        cout << "加载着色器失败" << endl;
        return 0;
    }

    // 创建着色器程序
    GLuint program = glCreateProgram();

    // 使用并链接shader
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // 检查链接状态
    GLint success = this->checkError(program, "PROGRAM");

    // 链接完成，删除着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return success ? program : 0;
}

GLint Shader::checkError(GLuint id, const char *type) {
    GLint success;
    char infoLog[512];
    if (type == "SHADER") {
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(id, 512, nullptr, infoLog);
            cout << "shader编译失败" << infoLog << endl;
        }
    } else {
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(id, 512, nullptr, infoLog);
            cout << "着色器程序链接失败" << infoLog << endl;
        }
    }

    return success;
}
