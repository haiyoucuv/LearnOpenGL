//
//  05_camera_class.hpp
//  TestOpenGL
//
//  Created by 还有醋v on 2020/6/20.
//  Copyright © 2020 还有醋v. All rights reserved.
//

#ifndef _5_camera_class_hpp
#define _5_camera_class_hpp

#include <glad.h>
#include <glfw3.h>

#include <iostream>
#include <math.h>
#include <string>

#include "stb_image.h"

#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.hpp"

using namespace std;

void processInput(GLFWwindow *window, float dt);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

int cameraClass(GLFWwindow* window);

#endif /* _5_camera_class_hpp */
