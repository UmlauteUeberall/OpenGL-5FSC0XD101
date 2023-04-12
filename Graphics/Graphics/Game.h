#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <iostream>

#include "Shader.h"

void FrameBufferSizeCallback(GLFWwindow* _window, int _width, int _height);

class CGame
{
public:
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	const char* WINDOW_TITLE = "Super Fancy Project";


private:
	GLFWwindow* m_window = nullptr;

	CShader* m_defaultShader;

	unsigned int m_texture1;
	unsigned int m_texture2;
	
	unsigned int m_VBO = 0;   // Vertex Buffer Object
	unsigned int m_VAO = 0;   // Vertex Array Object
	unsigned int m_EBO = 0;   // Element Buffer Object (Indexbuffer)

	CGame()
	{}


public:
	static CGame* Get()
	{
		static CGame* instance = new CGame();
		return instance;
	}

	int Initialize();
	int Run();
	void Finalize();

	unsigned int LoadTexture(const char* _path);

private:

};

