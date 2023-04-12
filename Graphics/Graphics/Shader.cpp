#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <Windows.h>

CShader::CShader(const char* _vertexPath, const char* _fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(_vertexPath);
		fShaderFile.open(_fragmentPath);

		std::stringstream vShaderStream;
		std::stringstream fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& _e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << _e.what() << std::endl;
        return;
	}
    const char* vertexCodeC = vertexCode.c_str();
    const char* fragmentCodeC = fragmentCode.c_str();

    // Vertexshader führt Umrechnungen in anderen Koordinatensyteme durch
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCodeC, nullptr);
    glCompileShader(vertexShader);
    CheckCompileErrors(vertexShader, "VERTEX");

    // Fragmentshader zeigt Pixel auf dem Bildschirm an
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCodeC, nullptr);
    glCompileShader(fragmentShader);
    CheckCompileErrors(vertexShader, "FRAGMENT");

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    CheckCompileErrors(m_shaderProgram, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void CShader::Use()
{
    glUseProgram(m_shaderProgram);
}

void CShader::CleanUp()
{
    glDeleteProgram(m_shaderProgram);
}

bool CShader::CheckCompileErrors(int _shaderID, std::string _type)
{
    int success;
    char infoLog[1024];
    if (_type != "PROGRAM")
    {
        glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(_shaderID, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_FAILED: " << _type << "\n" << infoLog << std::endl;
            return false;
        }
    }
    else
    {
        glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(m_shaderProgram, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            return -6;
        }
    }

    return true;
}
