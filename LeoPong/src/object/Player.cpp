#include "Player.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "window/Window.h"

Player::Player(float x, float y, float width, float height, Shader &shader, Renderer &renderer, Camera &camera) :
	_object(nullptr),
	_renderer(renderer),
	_width(width),
	_height(height),
	MOVE_SPEED(0.9f),
	_yPos(0.0f)
{
    float bottomX = 0.0f - ( width / 2.0f *  _renderer.GetVerticalA());
    float bottomY = 0.0f - ( height / 2.0f * _renderer.GetHorizontalA());
    float topX = 0.0f + ( width / 2.0f * _renderer.GetVerticalA());
    float topY = 0.0f + ( height / 2.0f * _renderer.GetHorizontalA());
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
    
    _binds[Bind::MOVEUP]   = GLFW_KEY_W;
    _binds[Bind::MOVEDOWN] = GLFW_KEY_S;

    SetPos(x, y);
}

Player::~Player() {
    delete _object;
}

void Player::BindKey(const Bind &bind, int action) {
    _binds[bind] = action;
}

void Player::Move(float x, float y) {
    _object->Move(x, y);
	_yPos += y;
}

void Player::SetPos(float x, float y) {
    _object->SetPos(x, y);
}

void Player::RotateR(float radians, float pitch, float yaw, float roll) {
    _object->RotateR(radians, pitch, yaw, roll);
}

void Player::RotateD(float degrees, float pitch, float yaw, float roll) {
    _object->RotateD(degrees, pitch, yaw, roll);
}

void Player::SetRotR(float radians, float pitch, float yaw, float roll) {
    _object->SetRotR(radians, pitch, yaw, roll);
}

void Player::SetRotD(float degrees, float pitch, float yaw, float roll) {
    _object->SetRotD(degrees, pitch, yaw, roll);
}

void Player::Draw(double Delta) {
    CheckInput(Delta);
    _object->Draw();
}

void Player::CheckInput(double Delta) {
    
	const int KEYMOVEUP = _binds[Bind::MOVEUP];
	const int KEYMOVEDOWN = _binds[Bind::MOVEDOWN];

	float TOPPOS;
	float BOTPOS;
	
	if (Window::IsKeyDown(KEYMOVEUP)) {
		Move(0.0f, MOVE_SPEED * Delta);

		TOPPOS = _yPos + (_height / 2.0f);

		if (TOPPOS > 1.0f) {
			
			Move(0.0f, - (TOPPOS - 1.0f));
		}
		
	}

	if (Window::IsKeyDown(KEYMOVEDOWN)) {
		Move(0.0f, -(MOVE_SPEED * Delta));

		BOTPOS = _yPos - (_height / 2.0f);

		if (BOTPOS < -1.0f) {

			Move(0.0f, -(BOTPOS + 1.0f));
		}
	}

}
