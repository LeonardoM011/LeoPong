#include "Object.h"
#include <glm/gtc/matrix_transform.hpp>

Object::Object(const std::vector<float> &buffer, const std::vector<unsigned int> &indices, Shader &shader, Renderer &renderer, Camera &camera) :
    _buffer(buffer),
    _indices(indices),
    _vb(&buffer[0], buffer.size() * sizeof(float)),
    _ib(nullptr),
    _renderer(renderer),
    _camera(camera),
    _shader(shader),
    _modelMat(1.0f),
    _translate(glm::vec3(0.0f, 0.0f, 0.0f)),
    _rotation(glm::vec3(0.0f, 0.0f, 0.0f))
{
    _shader.Bind();
    _layout.Push<float>(2);
	_layout.Push<float>(2);
    _va.AddBuffer(_vb, _layout);
    _ib = new IndexBuffer(&indices[0], indices.size());
    _shader.UnBind();
}

Object::~Object() {
    delete _ib;
}

void Object::Move(float x, float y) {
    _translate = glm::vec3(_translate.x + x, _translate.y + y, _translate.z);
}

void Object::SetPos(float x, float y) {
    _translate = glm::vec3(x, y, _translate.z);
}

void Object::RotateR(float radians, float pitch, float yaw, float roll) {
    _rotation.x += radians * pitch;
    _rotation.y += radians * yaw;
    _rotation.z += radians * roll;
}

void Object::RotateD(float degrees, float pitch, float yaw, float roll) {
    _rotation.x += glm::radians(degrees) * pitch;
    _rotation.y += glm::radians(degrees) * yaw;
    _rotation.z += glm::radians(degrees) * roll;
}

void Object::SetRotR(float radians, float pitch, float yaw, float roll) {
    _rotation.x = radians * pitch;
    _rotation.y = radians * yaw;
    _rotation.z = radians * roll;
}

void Object::SetRotD(float degrees, float pitch, float yaw, float roll) {
    _rotation.x = glm::radians(degrees) * pitch;
    _rotation.y = glm::radians(degrees) * yaw;
    _rotation.z = glm::radians(degrees) * roll;
}

void Object::Draw() {
    _shader.Bind();

    glm::vec3 translationVec = _translate;
    translationVec.x *= _renderer.GetVerticalA();
    translationVec.y *= _renderer.GetHorizontalA();
    _modelMat = glm::translate(glm::mat4(1.0f), translationVec);
    _modelMat = glm::rotate(_modelMat, _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    _modelMat = glm::rotate(_modelMat, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    _modelMat = glm::rotate(_modelMat, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    
    glm::mat4 MVP = _renderer.GetProjMat() * _camera.GetViewMat() * _modelMat;

	_shader.SetUniformMat4f("u_MVP", MVP);
	_renderer.Draw(_va, *_ib, _shader);
    _shader.UnBind();
}
