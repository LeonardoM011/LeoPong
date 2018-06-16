#include "IndexBuffer.h"
#include "../Renderer/Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) :
	_count(count) 
{
	// If unsigned int is not 4 bytes then assert
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	// Generate id
	GLCall(glGenBuffers(1, &_rendererID));
	// Bind the id
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID));
	// Pass in data to buffer
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
	// Delete buffers
	GLCall(glDeleteBuffers(1, &_rendererID));
}

void IndexBuffer::Bind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID));
}

void IndexBuffer::Unbind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
