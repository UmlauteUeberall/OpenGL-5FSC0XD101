#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <iostream>
#include <list>
#include "Shader.h"
#include "Entity.h"
#include <map>
#include "FrameBuffer.h"

void FrameBufferSizeCallback(GLFWwindow* _window, int _width, int _height);
//void MouseCallBack(GLFWwindow* _window, double _xpos, double _ypos);

class CGame
{
public:
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 1024;
	const char* WINDOW_TITLE = "Super Fancy Project";
	const float CAMERA_SPEED = 4;
	const float CAMERA_ROTATION_SPEED = 5;

	std::map<const char*, CShader*> m_shaders;
	//CShader* m_defaultShader;
	//CShader* m_phongShader;


	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraUp;
	glm::vec3 m_cameraRight;

	glm::vec3 m_AmbientColor;
	glm::vec3 m_DiffuseColor;
	glm::vec3 m_SpecularColor;
	glm::vec3 m_LightDir;

	float m_cameraYaw;
	float m_cameraPitch;
	//float Roll;

	glm::vec2 m_mouseDelta;

	byte m_oldKeys[316];
	byte m_currentKeys[316];

	inline double DeltaTime()
	{
		return m_deltaTime;
	}

	inline GLFWwindow* GetWindow()
	{
		return m_window;
	}

private:
	GLFWwindow* m_window = nullptr;
	double m_deltaTime;

	std::list<CEntity*> m_entitites;
	std::list<CEntity*> m_entititesToDelete;

	CFrameBuffer* m_frameBuffer;

	//glm::mat4 m_viewMatrix;
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
	unsigned int LoadTexture(const char* _path, int* _width, int* _height);

	bool KeyDown(int _keyCode);
	bool KeyUp(int _keyCode);
	bool Key(int _keyCode);
private:
	void LoadLevel();
	void ProcessInput();
};

