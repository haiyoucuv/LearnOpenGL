//
//  Appaction.hpp
//  TestOpenGL
//
//  Created by 还有醋v on 2020/6/7.
//  Copyright © 2020 还有醋v. All rights reserved.
//

#ifndef Appaction_hpp
#define Appaction_hpp

#include <glad.h>
#include <glfw3.h>

#include <iostream>
#include <math.h>
#include <string>

#include "Shader.h"

using namespace std;

class Appaction {
public:
	GLFWwindow* window;

public:
    Appaction();
    ~Appaction();

private:
    GLFWwindow * init(int width, int height);
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
};

#endif /* Appaction_hpp */
