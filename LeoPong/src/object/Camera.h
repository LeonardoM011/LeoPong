#pragma once
#include <glm/glm.hpp>

class Camera {
public:
    Camera(float x, float y);
    ~Camera();
    void SetPos(float x, float y);
    void Move(float x, float y);
    void RotateR(float radians, float pitch, float yaw, float roll);
    void RotateD(float degrees, float pitch, float yaw, float roll);
    void SetRotR(float radians, float pitch, float yaw, float roll);
    void SetRotD(float degrees, float pitch, float yaw, float roll);
    glm::mat4 GetViewMat();
private:
    glm::mat4 _viewMat;
    glm::vec3 _translate;
    glm::vec3 _rotation;
};