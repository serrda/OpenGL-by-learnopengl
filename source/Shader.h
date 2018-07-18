#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
private:
	// Program ID
	unsigned int ID;
public:
	// Constructor - reads and builds the shader
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	// Activates the shader
	void use();

	// Utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
};
