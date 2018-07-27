#pragma once
#include <glad/glad.h>

class ElementBuffer
{
private:
	unsigned int m_ID;
	unsigned int m_Count;
public:
	ElementBuffer(const void *data, unsigned int count);
	~ElementBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
};

