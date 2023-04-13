#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <iostream>
#include <list>
#include "Shader.h"
#include "Entity.h"


void FrameBufferSizeCallback(GLFWwindow* _window, int _width, int _height);

class CGame
{
public:
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	const char* WINDOW_TITLE = "Super Fancy Project";


	CShader* m_defaultShader;
	glm::vec3 m_cameraPos;

	inline double DeltaTime()
	{
		return m_deltaTime;
	}

private:
	GLFWwindow* m_window = nullptr;
	double m_deltaTime;

	std::list<CEntity*> m_entitites;
	std::list<CEntity*> m_entititesToDelete;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

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

	bool AddEntity(CEntity* _entity);
	bool RemoveEntity(CEntity* _entity);
	bool ContainsEntity(CEntity* _entity);

	unsigned int LoadTexture(const char* _path);

private:
	void LoadLevel();
};

