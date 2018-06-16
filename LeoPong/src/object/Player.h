#pragma once
#include <vector>
#include <unordered_map>
#include "Object.h"

enum class Bind {
    MOVEUP,
    MOVEDOWN,
};

class Player {
public:
    Player(float x, float y, float width, float height, Shader &shader, Renderer &renderer, Camera &camera);
    ~Player();
    void BindKey(const Bind &bind, int action);
    void Move(float x, float y);
    void SetPos(float x, float y);
    void RotateR(float radians, float pitch, float yaw, float roll);
    void RotateD(float degrees, float pitch, float yaw, float roll);
    void SetRotR(float radians, float pitch, float yaw, float roll);
    void SetRotD(float degrees, float pitch, float yaw, float roll);
    void Draw(double Delta);
    void ChangeSpeed(float speed) { MOVE_SPEED = speed; }
private:
    void CheckInput(double Delta);
    float MOVE_SPEED;
    Object *_object;
    Renderer &_renderer;
    float _width;
    float _height;
    std::unordered_map<Bind, int> _binds;
	float _yPos;
};
