//
//  04_camera.hpp
//  TestOpenGL
//
//  Created by 还有醋v on 2020/6/9.
//  Copyright © 2020 还有醋v. All rights reserved.
//

#ifndef _4_camera_hpp
#define _4_camera_hpp

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

using namespace std;

int camera(GLFWwindow* window);

#endif /* _4_camera_hpp */
