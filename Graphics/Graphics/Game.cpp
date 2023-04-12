#include "Game.h"
#include "Vertex.h"
#include "stb_image.h"

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


	Vertex vertices[]
	{
		{Vector3(-0.5f, 0.5, 0.0), Vector3(0.882f, 0.0313f, 0.91f), Vector2(0,0)},
		{Vector3(0.5f, 0.5, 0.0), Vector3(1,0,0), Vector2(1,0)},
		{Vector3(0.5f, -0.5, 0.0), Vector3(1,1,0), Vector2(1,1)},
		{Vector3(-0.5f, -0.5, 0.0), Vector3(0.2f,0.49f,0.82f), Vector2(0,1)},
	};

	unsigned int indices[]
	{
		0, 1, 3,
		1, 2, 3
	};


	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, sizeof(Vector3) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, sizeof(Vector3) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, col));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, sizeof(Vector2) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	m_texture1 = LoadTexture("Test.jpg");
	m_texture2 = LoadTexture("Smiley2.png");

	return 0;
}

int CGame::Run()
{
	while (!glfwWindowShouldClose(m_window))
	{
		// Backbuffer clear
		glClear(GL_COLOR_BUFFER_BIT);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Variablen setzen
		m_defaultShader->SetFloat("textureBlend", sin(glfwGetTime()) / 2.0f + 0.5f);
		m_defaultShader->SetVector2("uvZoom", Vector2( sin(glfwGetTime()) / 2.0f + 0.5f,
															cos(glfwGetTime() * 0.23) * 2));
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture1);
		m_defaultShader->SetInt("tex1", 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_texture2);
		m_defaultShader->SetInt("tex2", 1);

		// Shader benutzung vorbereiten
		m_defaultShader->Use();
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glBindVertexArray(0);
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	return 0;
}

void CGame::Finalize()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);

	m_defaultShader->CleanUp();
	glfwTerminate();
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

void FrameBufferSizeCallback(GLFWwindow* _window, int _width, int _height)
{
	glViewport(0, 0, _width, _height);
}
