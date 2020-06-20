//
//  Camera.cpp
//  TestOpenGL
//
//  Created by 还有醋v on 2020/6/14.
//  Copyright © 2020 还有醋v. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera(glm::vec3 position, float fov, float aspect, float near, float far) {
    this->position = position;
    this->fov = fov;
    this->aspect = aspect;
    this->near = near;
    this->far = far;
    this->update(0);
}


Camera::~Camera() {

}

void Camera::lookAt(glm::vec3 target) {
    glm::vec3 zAxis = glm::normalize(target - this->position);
    glm::vec3 xAxis = glm::normalize(glm::cross(glm::normalize(worldUp), zAxis));
    glm::vec3 yAxis = glm::cross(zAxis, xAxis);

    glm::mat4 translation = glm::mat4(1.0f);
    translation[3][0] = -position.x;
    translation[3][1] = -position.y;
    translation[3][2] = -position.z;

    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0][0] = xAxis.x;
    rotation[1][0] = xAxis.y;
    rotation[2][0] = xAxis.z;

    rotation[0][1] = yAxis.x;
    rotation[1][1] = yAxis.y;
    rotation[2][1] = yAxis.z;

    rotation[0][2] = zAxis.x;
    rotation[1][2] = zAxis.y;
    rotation[2][2] = zAxis.z;

    this->view = rotation * translation;
}

void Camera::lookAt(float x, float y, float z) {
    this->lookAt(glm::vec3(x, y, z));
}

void Camera::update(float dt) {
    this->updateFront();
    this->updateProjection();
    this->updateView();
}

/**
 * 更新 view 矩阵
 */
void Camera::updateView() {
    this->view = glm::lookAt(
        this->position,
        this->position + this->front,
        this->up
    );
}

void Camera::updateProjection() {
    this->aspect = winWidth / winHeight;
    this->projection = glm::perspective(glm::radians(this->fov), this->aspect, this->near, this->far);
}

/**
 * 更新 front
 */
void Camera::updateFront() {
    glm::vec3 front = glm::vec3(0.0f, 0.0f, 0.0f);
    front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    front.y = sin(glm::radians(this->pitch));
    front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

    this->front = glm::normalize(front);
    this->right = glm::normalize(glm::cross(this->front, this->worldUp));
    this->up = glm::normalize(glm::cross(this->right, this->front));
}
