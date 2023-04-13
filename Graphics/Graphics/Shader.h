#pragma once

#include <glad/glad.h>
#include <vec2.hpp>
#include <vec3.hpp>
#include <string>
#include <gtc/matrix_transform.hpp>

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

	void SetInt(const char* _name, int _value)
	{
		glUniform1i(glGetUniformLocation(m_shaderProgram, _name), _value);
	}

	void SetFloat(const char* _name, float _value)
	{
		glUniform1f(glGetUniformLocation(m_shaderProgram, _name), _value);
	}

	void SetVector2(const char* _name, glm::vec2 _value)
	{
		glUniform2f(glGetUniformLocation(m_shaderProgram, _name), _value.x, _value.y);
	}

	void SetVector3(const char* _name, glm::vec3 _value)
	{
		glUniform3f(glGetUniformLocation(m_shaderProgram, _name), _value.x, _value.y, _value.z);
	}

	void SetMatrix(const char* _name, glm::mat4 _value)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, _name), 1, GL_FALSE, &_value[0][0]);
	}

	void CleanUp();

private:

	bool CheckCompileErrors(int _shaderID, std::string _type);

};

