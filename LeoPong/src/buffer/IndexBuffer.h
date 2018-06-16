#pragma once

class IndexBuffer {
public:
	IndexBuffer(const unsigned int *data, unsigned int count);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;
	inline unsigned int GetCount() const { return _count; }
private:
	unsigned int _rendererID;
	unsigned int _count;
};