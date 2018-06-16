#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float x, float y) :
    _translate(0.0f),
    _viewMat(1.0f),
    _rotation(0.0f)
{
    SetPos(x, y);
}

Camera::~Camera() {
    
}

void Camera::SetPos(float x, float y) {
    _translate = glm::vec3(-x, -y, _translate.z);
}

void Camera::Move(float x, float y) {
    _translate = glm::vec3(_translate.x - x, _translate.y - y, _translate.z);
}

void Camera::RotateR(float radians, float pitch, float yaw, float roll) {
    _rotation.x += radians * pitch;
    _rotation.y += radians * yaw;
    _rotation.z += radians * roll;
}

void Camera::RotateD(float degrees, float pitch, float yaw, float roll) {
    _rotation.x += glm::radians(degrees) * pitch;
    _rotation.y += glm::radians(degrees) * yaw;
    _rotation.z += glm::radians(degrees) * roll;
}

void Camera::SetRotR(float radians, float pitch, float yaw, float roll) {
    _rotation.x = radians * pitch;
    _rotation.y = radians * yaw;
    _rotation.z = radians * roll;
}

void Camera::SetRotD(float degrees, float pitch, float yaw, float roll) {
    _rotation.x = glm::radians(degrees) * pitch;
    _rotation.y = glm::radians(degrees) * yaw;
    _rotation.z = glm::radians(degrees) * roll;
}

glm::mat4 Camera::GetViewMat() {
    _viewMat = glm::translate(glm::mat4(1.0f), _translate);
    _viewMat = glm::rotate(_viewMat, -_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    _viewMat = glm::rotate(_viewMat, -_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    _viewMat = glm::rotate(_viewMat, -_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    return _viewMat;
}
