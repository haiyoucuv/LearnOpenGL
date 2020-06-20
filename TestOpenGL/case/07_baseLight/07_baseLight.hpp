//
//  06_light.hpp
//  TestOpenGL
//
//  Created by 还有醋v on 2020/6/20.
//  Copyright © 2020 还有醋v. All rights reserved.
//

#ifndef _7_baseLight_hpp
#define _7_baseLight_hpp

#include "const.hpp"

#include <glad.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

#include "Camera.hpp"
#include "Shader.h"

int baseLight(GLFWwindow* window);

void processInput7(GLFWwindow *window, float dt);
void mouse_callback7(GLFWwindow *window, double xpos, double ypos);
void scroll_callback7(GLFWwindow *window, double xoffset, double yoffset);

#endif /* 07_baseLight_hpp */
