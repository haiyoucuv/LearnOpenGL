//
//  Camera.hpp
//  TestOpenGL
//
//  Created by 还有醋v on 2020/6/14.
//  Copyright © 2020 还有醋v. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {

public:
    glm::vec3 position; // 位置
    glm::vec3 front;    // 方向向量
    glm::vec3 up;       // 上向量
    glm::vec3 right;    // 右向量
    glm::vec3 worldUp;  // 世界中的上向量

    float far;  // 最远可见
    float near; // 最近可见

    float fov;  // fov

    float yaw;      // 偏航角
    float pitch;    // 俯仰角
    float roll;     // 滚转角

public:
    Camera();

    ~Camera();

    glm::mat4 getViewMatrix();

private:

};

#endif /* Camera_hpp */
