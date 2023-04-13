#include "Game.h"
#include "Vertex.h"
#include "stb_image.h"
#include "Quad.h"
#include "Cube.h"


int CGame::Initialize()
{
	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
	if (!m_window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		return -2;
	}

	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, FrameBufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -3;
	}

	glClearColor(0, 0.5f, 1, 1);

	m_defaultShader = new CShader("defaultShader.vert", "defaultShader.frag");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_cameraPos = glm::vec3(0, 0, -3);

	

	LoadLevel();

	return 0;
}

int CGame::Run()
{
	double oldTime = glfwGetTime();
	double currentTime = oldTime;
	while (!glfwWindowShouldClose(m_window))
	{
		// Backbuffer clear
		glClear(GL_COLOR_BUFFER_BIT);
		oldTime = currentTime;
		currentTime = glfwGetTime();
		m_deltaTime = currentTime - oldTime;
		
		for (auto itr : m_entitites)
		{
			itr->Update();
		}

		m_viewMatrix = glm::mat4(1.0f);
		m_viewMatrix = glm::translate(m_viewMatrix, m_cameraPos);
		m_defaultShader->SetMatrix("view", m_viewMatrix);
		
		m_projectionMatrix = glm::mat4(1.0f);
		m_projectionMatrix = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		m_defaultShader->SetMatrix("projection", m_projectionMatrix);

		for (auto itr : m_entitites)
		{
			itr->Render();
		}

		for (auto itr : m_entititesToDelete)
		{
			m_entitites.remove(itr);
			itr->CleanUp();
			delete(itr);
		}

		glBindVertexArray(0);
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	return 0;
}

void CGame::Finalize()
{
	for (auto itr : m_entititesToDelete)
	{
		m_entitites.remove(itr);
		itr->CleanUp();
		delete(itr);
	}

	for (auto itr : m_entitites)
	{
		itr->CleanUp();
		delete(itr);
	}

	m_defaultShader->CleanUp();
	glfwTerminate();
}

bool CGame::AddEntity(CEntity* _entity)
{
	if (!_entity || ContainsEntity(_entity))
	{
		return false;
	}

	if (_entity->Initialize())
	{
		m_entitites.push_back(_entity);
		return true;
	}

	return false;
}

bool CGame::RemoveEntity(CEntity* _entity)
{
	if (!_entity || !ContainsEntity(_entity))
	{
		return false;
	}
	m_entititesToDelete.push_back(_entity);

	return true;
}

bool CGame::ContainsEntity(CEntity* _entity)
{
	if (!_entity)
	{
		return false;
	}

	for (auto itr : m_entitites)
	{
		if (itr == _entity)
		{
			return true;
		}
	}

	return false;
}

unsigned int CGame::LoadTexture(const char* _path)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannel;
	// unsere (0,0) ist links oben
	stbi_set_flip_vertically_on_load(false);
	unsigned char* data = stbi_load(_path, &width, &height, &nrChannel, 0);
	if (data)
	{
		if (nrChannel == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else if (nrChannel == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		return texture;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return -4;
	}
	stbi_image_free(data);
}

void CGame::LoadLevel()
{
	//AddEntity(new CQuad(glm::vec3(0,0,0)));
	AddEntity(new CCube(glm::vec3(0,0,0)));
}

void FrameBufferSizeCallback(GLFWwindow* _window, int _width, int _height)
{
	glViewport(0, 0, _width, _height);
}
