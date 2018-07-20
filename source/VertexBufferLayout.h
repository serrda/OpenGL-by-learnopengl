#pragma once

#include <vector>
#include "glad\glad.h"


struct VertexBufferElement
{
	unsigned int count;
	unsigned int type;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_UNSIGNED_INT: return 4;
		case GL_FLOAT: return 4;
		case GL_BYTE: return 1;
		}
		return 0;
	}
};


class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout() : m_Stride(0) {}

	template<typename T>
	void Push(unsigned int _count)
	{
		return;
	}

	template<>
	void Push<float>(unsigned int _count)
	{
		m_Elements.push_back({ _count, GL_FLOAT, GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * _count;
	}

	template<>
	void Push<unsigned int>(unsigned int _count)
	{
		m_Elements.push_back({ _count, GL_UNSIGNED_INT, GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * _count;
	}

	template<>
	void Push<unsigned char>(unsigned int _count)
	{
		m_Elements.push_back({ _count, GL_UNSIGNED_BYTE, GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * _count;
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};