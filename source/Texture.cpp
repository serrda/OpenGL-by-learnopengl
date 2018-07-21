#pragma once

#include "Texture.h"
#include <string>
#include "stb_image/stb_image.h"
#include <iostream>

Texture::Texture()
{
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);
	SetParams();
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_ID);
}

Texture::Texture(const std::string _path, GLenum _format)
{
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);
	SetParams();
	LoadImg(_path, _format);
}

void Texture::Bind(unsigned int _slot) const
{
	glActiveTexture(GL_TEXTURE0 + _slot);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetParams() const
{
	// Setting the texture wrapping/filtering options(on currently bount texture oject)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
}

void Texture::LoadImg(const std::string _path, GLenum _format) const
{
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(_path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, _format, GL_UNSIGNED_BYTE, data);
		/* Previous func args:
		1. Texture target
		2. Mipmap level - manual setting
		3. Format to store the texture - image has only rgb values so rgb values are stored (!!! Change for maps)
		4,5. Width, height - correspondingly
		6. Should always be 0 - legacy staff
		7,8. Format and datatype of source image - we loaded RGB values and stored as chars(bytes) (!!! Change for maps)
		9. Actual image data (pointer)
		*/
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << _path << std::endl;
	}
	stbi_image_free(data);
}
