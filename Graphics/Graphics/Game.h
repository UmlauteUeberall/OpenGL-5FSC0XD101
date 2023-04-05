#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <iostream>

void FrameBufferSizeCallback(GLFWwindow* _window, int _width, int _height);

class CGame
{
public:
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	const char* WINDOW_TITLE = "Super Fancy Project";


private:
	GLFWwindow* m_window = nullptr;

	const char* m_vertexShaderSource = "#version 460 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos, 1.0);\n"
		"}\0";
	const char* m_fragmentShaderSource = "#version 460 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1,0.5,0,1);\n"
		"}\0";

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

private:

};

