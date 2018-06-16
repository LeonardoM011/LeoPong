#include "Slab.h"
#include <GLFW/glfw3.h>

Slab::Slab(float x, float y, float width, float height, Shader &shader, Renderer &renderer, Camera &camera) :
    _object(nullptr)
{
    float bottomX = 0.0f - ( width / 2.0f );
    float bottomY = 0.0f - ( height / 2.0f );
    float topX = 0.0f + ( width / 2.0f );
    float topY = 0.0f + ( height / 2.0f );
    std::vector<float> buffer = {
        bottomX, bottomY,  0.0f, 0.0f,
		bottomX, topY,     0.0f, 1.0f,
	    topX,    topY,     1.0f, 1.0f,
		topX,    bottomY,  1.0f, 0.0f
    };
    std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};
    _object = new Object(buffer, indices, shader, renderer, camera);

    SetPos(x, y);
}

Slab::~Slab() {
    delete _object;
}

void Slab::Move(float x, float y) {
    _object->Move(x, y);
}

void Slab::SetPos(float x, float y) {
    _object->SetPos(x, y);
}

void Slab::RotateR(float radians, float pitch, float yaw, float roll) {
    _object->RotateR(radians, pitch, yaw, roll);
}

void Slab::RotateD(float degrees, float pitch, float yaw, float roll) {
    _object->RotateD(degrees, pitch, yaw, roll);
}

void Slab::SetRotR(float radians, float pitch, float yaw, float roll) {
    _object->SetRotR(radians, pitch, yaw, roll);
}

void Slab::SetRotD(float degrees, float pitch, float yaw, float roll) {
    _object->SetRotD(degrees, pitch, yaw, roll);
}

void Slab::Draw() {
    _object->Draw();
}
