#include "Shader.h"
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath)
{
	// 1. Retrieving the vertex/fragment source codes from filepath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// Ensuring ifstream objects can throw exceptions
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try
	{
		// Opening files:
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// Reading files's buffer contets into streams:
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// Closing files:
		vShaderFile.close();
		fShaderFile.close();
		// Convert stream into string:
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	
	// 2. Compiling shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];
	
	/* Vertex Shader
	1. Creating shader
	2. Attaching it to its source code(stored as const char*)
	3. Compiling shader
	4. Shader ready to use */
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// Print compile errors if any:
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/* Fragment Shader
	1. Creating shader
	2. Attaching it to its source code(stored as const char*)
	3. Compiling shader
	4. Shader ready to use */
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// Print compile errors if any:
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/* Shader Program
	Is the final linked version of multiple shaders combined.
	1. Create program
	2. Attach shaders one by one to this program
	3. Link them after attaching */

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	// Print linking errors if any:
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// Delete shaders after linking, they are not longer necessary needed
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() 
{
	glUseProgram(ID);
}

void Shader::setUniform1b(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setUniform1i(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setUniform1f(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setUniform3f(const std::string & name, float value0, float value1, float value2) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value0, value1, value2);
}
void Shader::setUniform4f(const std::string & name, float value0, float value1, float value2, float value3) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), value0, value1, value2, value3);
}

void Shader::setUniformMatrix4fv(const std::string &name, glm::mat4 _matrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(_matrix));
}

