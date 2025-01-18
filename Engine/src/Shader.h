#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <iostream>
#include <glad/glad.h>

class Shader
{
public:
	// the program ID
	unsigned int ID;

	// constructur reads and builds the shader
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	Shader(const Shader& other);
	Shader& operator=(const Shader& other);
	// use/activate the shader
	void use();
	// utility uniform functions
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;

	bool operator==(const Shader& rhs) const { return ID == rhs.ID; }
	bool operator!=(const Shader& rhs) const { return *this != rhs; }
};

#endif
