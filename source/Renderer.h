#pragma once

#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Shader.h"

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray & _va, const ElementBuffer & _eb, Shader & _shader) const;
	void Draw(const VertexArray & _va, Shader & _shader) const;
};