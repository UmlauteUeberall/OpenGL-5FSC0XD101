#pragma once

#include <glad/glad.h>

#include <string>

class CShader
{
public:
	unsigned int m_shaderProgram = 0;

	CShader(const char* _vertexPath, const char* _fragmentPath);

	void Use();

	void SetBool(const char* _name, bool _value)
	{
		glUniform1i(glGetUniformLocation(m_shaderProgram, _name), _value);
	}

	void SetInt(const char* _name, bool _value)
	{
		glUniform1i(glGetUniformLocation(m_shaderProgram, _name), _value);
	}

	void SetFloat(const char* _name, bool _value)
	{
		glUniform1f(glGetUniformLocation(m_shaderProgram, _name), _value);
	}

	void CleanUp();

private:

	bool CheckCompileErrors(int _shaderID, std::string _type);

};

