//
//  04_camera.hpp
//  TestOpenGL
//
//  Created by 还有醋v on 2020/6/9.
//  Copyright © 2020 还有醋v. All rights reserved.
//

#ifndef _4_camera_hpp
#define _4_camera_hpp

#include "const.hpp"

#include <glad.h>
#include <glfw3.h>

#include "stb_image.h"

#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void processInput(GLFWwindow *window, float dt, glm::vec3 *cameraPos, glm::vec3 *cameraFront, glm::vec3 *cameraUp);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

int camera(GLFWwindow* window);

#endif /* _4_camera_hpp */
