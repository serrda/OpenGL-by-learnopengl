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
	void setUniform1b(const std::string &name, bool value) const;
	void setUniform1i(const std::string &name, int value) const;
	void setUniform1f(const std::string &name, float value) const;
	void setUniform3f(const std::string &name, float value0, float value1, float value2) const;
	void setUniform4f(const std::string &name, float value0, float value1, float value2, float value3) const;
};
