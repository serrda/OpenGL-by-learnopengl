#pragma once

#include "glad\glad.h"
#include <string>

class Texture
{
private:
	unsigned int m_ID;
	std::string path;
public:
	Texture();
	~Texture();

	Texture(const std::string _path, GLenum _format);

	void Bind(unsigned int _slot) const;
	void Unbind() const;
	void SetParams() const;
	void LoadImg(const std::string _path, GLenum _format) const;
	unsigned int GetID() const { return m_ID; }
};