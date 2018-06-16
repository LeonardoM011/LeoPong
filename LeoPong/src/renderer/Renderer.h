#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "buffer/VertexArray.h"
#include "buffer/IndexBuffer.h"
#include "shader/Shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();

#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char *function, const char *file, int line);

class Renderer {
public:
	Renderer();
	~Renderer();
	void ChangeBackgroundColor(float r, float g, float b) const;
	void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
	void Clear() const;
	glm::mat4 GetProjMat() const { return _projMat; }
	float GetVerticalA() const { return _verticalA; }
	float GetHorizontalA() const { return _horizontalA; }
private:
	glm::mat4 _projMat;
	float _verticalA;
	float _horizontalA;
};
