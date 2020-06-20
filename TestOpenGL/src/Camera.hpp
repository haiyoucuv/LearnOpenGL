//
//  Camera.hpp
//  TestOpenGL
//
//  Created by 还有醋v on 2020/6/14.
//  Copyright © 2020 还有醋v. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "const.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {

public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f); // 位置
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);    // 方向向量
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);       // 上向量
    glm::vec3 right;    // 右向量
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);  /// TODO maybe 世界中的上向量

    float fov = 45.0f;  // fov
    float aspect = 1.0f;    // 画面比例
    float far = 100.0f;  // 最远可见
    float near = 0.1f; // 最近可见


    float yaw = -90.0f;      // 偏航角
    float pitch = 0.0f;    // 俯仰角
    float roll = 0.0f;     // 滚转角

    glm::mat4 view;
    glm::mat4 projection;

public:
    Camera(glm::vec3 position, float fov, float aspect, float near, float far);

    ~Camera();

    void lookAt(glm::vec3 target);

    void lookAt(float x, float y, float z);

    void update(float dt);

private:
    void updateView();
    void updateProjection();
    void updateFront();

};

#endif /* Camera_hpp */
