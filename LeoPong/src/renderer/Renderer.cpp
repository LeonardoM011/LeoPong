#include "Renderer.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Renderer::Renderer() :
	_verticalA(2.0f),
	_horizontalA(1.5f)
{
	// Enabling GL Blending
	GLCall(glEnable(GL_BLEND));
	// Enabling Alpha Blending
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	_projMat = glm::ortho(- _verticalA, _verticalA, - _horizontalA, _horizontalA, -1.0f, 1.0f);

	GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
}

Renderer::~Renderer() {

}

void Renderer::ChangeBackgroundColor(float r, float g, float b) const {
	GLCall(glClearColor(r, g, b, 1.0f));
}

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char *function, const char *file, int line) {
	while (GLenum error = glGetError()) {
		std::cerr << "OpenGL Error: (" << error << ")\nfunc: " << function << "\nfile: \"" << file << "\": " << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const {
	// Binding Shader
	shader.Bind();
	// Binding Vertex Array
	va.Bind();
	// Drawing
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const {
	// Flushing Color and Depth Buffer
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
