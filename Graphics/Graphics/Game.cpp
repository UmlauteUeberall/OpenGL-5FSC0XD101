#include "Game.h"
#include "Vertex.h"
#include "stb_image.h"
#include "Quad.h"
#include "Cube.h"
#include "PhongCube.h"
#include "Terrain.h"


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
	glfwSetCursorPosCallback(m_window, MouseCallBack);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -3;
	}

	glClearColor(0, 0.5f, 1, 1);

	m_shaders["default"] = new CShader("defaultShader.vert", "defaultShader.frag");
	m_shaders["phong"] = new CShader("phongShader.vert", "phongShader.frag");
	m_shaders["terrain"] = new CShader("terrain.vert", "terrain.frag");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	m_cameraPos = glm::vec3(0, 4, -5);
	m_cameraYaw = 90;
	m_cameraPitch = -45;

	m_projectionMatrix = glm::mat4(1.0f);
	m_projectionMatrix = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

	for (auto itr : m_shaders)
	{
		itr.second->Use();
		itr.second->SetMatrix("projection", m_projectionMatrix);
	}

	m_AmbientColor = glm::vec3(0.1f, 0.1f, 0.1f);
	m_DiffuseColor = glm::vec3(0.8f, 0.8f, 0.8f);
	m_SpecularColor = glm::vec3(1.0f, 1.0f, 1.0f);
	m_LightDir = glm::vec3(0.1f, -1.0f, 1.0f);

	LoadLevel();

	return 0;
}

int CGame::Run()
{
	double oldTime = glfwGetTime();
	double currentTime = oldTime;


	while (!glfwWindowShouldClose(m_window))
	{
		oldTime = currentTime;
		currentTime = glfwGetTime();
		m_deltaTime = currentTime - oldTime;

		if (glfwGetKey(m_window, GLFW_KEY_A))
		{
			m_cameraPos.x += m_deltaTime * CAMERA_SPEED;
		}
		if (glfwGetKey(m_window, GLFW_KEY_D))
		{
			m_cameraPos.x -= m_deltaTime * CAMERA_SPEED;
		}
		if (glfwGetKey(m_window, GLFW_KEY_W))
		{
			m_cameraPos.z += m_deltaTime * CAMERA_SPEED;
		}
		if (glfwGetKey(m_window, GLFW_KEY_S))
		{
			m_cameraPos.z -= m_deltaTime * CAMERA_SPEED;
		}
		if (glfwGetKey(m_window, GLFW_KEY_Q))
		{
			m_cameraPos.y -= m_deltaTime * CAMERA_SPEED;
		}
		if (glfwGetKey(m_window, GLFW_KEY_E))
		{
			m_cameraPos.y += m_deltaTime * CAMERA_SPEED;
		}

		//m_cameraYaw += m_mouseDelta.x * m_deltaTime * CAMERA_ROTATION_SPEED;
		//m_cameraPitch += m_mouseDelta.y * m_deltaTime * CAMERA_ROTATION_SPEED;

		m_cameraFront.x = cos(glm::radians(m_cameraYaw)) * cos(glm::radians(m_cameraPitch));
		m_cameraFront.y = sin(glm::radians(m_cameraPitch));
		m_cameraFront.z = sin(glm::radians(m_cameraYaw)) * cos(glm::radians(m_cameraPitch));

		m_cameraFront = glm::normalize(m_cameraFront);
		m_cameraRight = glm::normalize(glm::cross(m_cameraFront, glm::vec3(0, 1, 0)));
		m_cameraUp = glm::normalize(glm::cross(m_cameraRight, m_cameraFront));

		for (auto itr : m_entitites)
		{
			itr->Update();
		}

		// Backbuffer clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//m_viewMatrix = glm::mat4(1.0f);
		//m_viewMatrix = glm::translate(m_viewMatrix, m_cameraPos);

		for (auto itr : m_shaders)
		{
			itr.second->Use();
			itr.second->SetMatrix("view", glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp));
			itr.second->SetVector3("AmbientColor", m_AmbientColor);
			itr.second->SetVector3("DiffuseColor", m_DiffuseColor);
			itr.second->SetVector3("SpecularColor", m_SpecularColor);
			itr.second->SetVector3("LightDir", m_LightDir);
			itr.second->SetVector3("CameraPos", m_cameraPos);
		}


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

	for (auto itr : m_shaders)
	{
		itr.second->CleanUp();
	}
	m_shaders.clear();
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
	int width, height;
	return LoadTexture(_path, &width, &height);
}

unsigned int CGame::LoadTexture(const char* _path, int* _width, int* _height)
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
		(*_width) = width;
		(*_height) = height;
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
	for (int i = 0; i < 10; i++)
	{
		AddEntity(new CCube(glm::vec3(i - 5, 0, 0)));
	}

	AddEntity(new CPhongCube(glm::vec3(0, 1, -2)));

	AddEntity(new CTerrain(glm::vec3(0, -10, 0), 100, 50));
	//AddEntity(new CPhongCube(glm::vec3(0, -10, -2)));

}

void FrameBufferSizeCallback(GLFWwindow* _window, int _width, int _height)
{
	glViewport(0, 0, _width, _height);
}

void MouseCallBack(GLFWwindow* _window, double _xpos, double _ypos)
{
	glm::vec2 mousePos = glm::vec2(_xpos, _ypos);

	CGame::Get()->m_mouseDelta = mousePos - CGame::Get()->m_oldMousePos;
}
