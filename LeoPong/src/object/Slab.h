#pragma once
#include "Object.h"

class Slab {
public:
    Slab(float x, float y, float width, float height, Shader &shader, Renderer &renderer, Camera &camera);
    ~Slab();
    void Move(float x, float y);
    void SetPos(float x, float y);
    void RotateR(float radians, float pitch, float yaw, float roll);
    void RotateD(float degrees, float pitch, float yaw, float roll);
    void SetRotR(float radians, float pitch, float yaw, float roll);
    void SetRotD(float degrees, float pitch, float yaw, float roll);
    void Draw();
private:
    Object *_object;
};
