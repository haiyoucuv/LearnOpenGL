//
// Created by 还有醋v on 2020/5/31.
// Copyright (c) 2020 还有醋v. All rights reserved.
//

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

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
    Shader(string vertexPath, string fragmentPath);

    // 析构函数
    ~Shader();

    void use();

    GLint getUniformLocation(const GLchar *name);

    void setMat4(const GLchar *name, glm::mat4 value);

    void setVec3(const GLchar *name, glm::vec3 value);

    void setVec3(const GLchar *name, float x, float y, float z);

    void setBool(const string &name, bool value) const;

    void setInt(const string &name, int value) const;

    void setFloat(const string &name, float value) const;


private:
    GLuint createShader(const char *shaderCode, GLenum type);

    GLuint createProgram(const char *vertexShaderCode, const char *fragmentShaderCode);

    GLint checkError(GLuint id, const char *type);
};


#endif // SHADER_H
