//
// Created by 还有醋v on 2020/5/31.
// Copyright (c) 2020 还有醋v. All rights reserved.
//

#ifndef SHADER_H
#define SHADER_H


#include <glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    // Shader程序的id
    GLuint id;

    /**
     * 构造函数
     * @param vertexPath
     * @param fragmentPath
     */
    // Shader(const char *vertexPath, const char *fragmentPath);
    Shader(std::string vertexPath, std::string fragmentPath);

    // 析构函数
    ~Shader();

    void use();

    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

private:
    GLuint createShader(const char *shaderCode, GLenum type);

    GLuint createProgram(const char *vertexShaderCode, const char *fragmentShaderCode);

    GLint checkError(GLuint id, const char *type);
};


#endif // SHADER_H
