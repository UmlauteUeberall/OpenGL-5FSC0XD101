#include "PhongCube.h"
#include "Game.h"

CPhongCube::CPhongCube(glm::vec3 _pos)
	: CEntity(_pos)
{
	int width, height;

	m_mainTexture = CGame::Get()->LoadTexture("RainbowTest.jpg", &width, &height);
	m_normalTexture = CGame::Get()->LoadTexture("RainbowTestNormal.jpg");

	m_vertexCount = 4 * 6;
	m_indexCount = 36;

	m_vertices = new Vertex[m_vertexCount];
	m_indices = new unsigned int[m_indexCount];

	glm::vec2 halfPixel = glm::vec2(0.5, 0.5) / glm::vec2(width, height);

	int i = 0;
	// oben
	m_vertices[i++] = { glm::vec3(-0.5f, 0.5, 0.5),		glm::vec2(0.5 - halfPixel.x,0 + halfPixel.y),	glm::vec3(0, 1, 0) };
	m_vertices[i++] = { glm::vec3(0.5f, 0.5, 0.5),		glm::vec2(0 + halfPixel.x,0 + halfPixel.y),		glm::vec3(0, 1, 0) };
	m_vertices[i++] = { glm::vec3(0.5f, 0.5, -0.5),		glm::vec2(0 + halfPixel.x,0.5 - halfPixel.y),	glm::vec3(0, 1, 0) };
	m_vertices[i++] = { glm::vec3(-0.5f, 0.5, -0.5),	glm::vec2(0.5 - halfPixel.x,0.5 - halfPixel.y), glm::vec3(0, 1, 0) };

	// vorne
	m_vertices[i++] = { glm::vec3(-0.5f, 0.5, -0.5), glm::vec2(1 - halfPixel.x,0 + halfPixel.y), glm::vec3(0, 0, -1) };
	m_vertices[i++] = { glm::vec3(0.5f, 0.5, -0.5),		glm::vec2(0.5 + halfPixel.x,0 + halfPixel.y), glm::vec3(0, 0, -1) };
	m_vertices[i++] = { glm::vec3(0.5f, -0.5, -0.5),	glm::vec2(0.5 + halfPixel.x,0.5 - halfPixel.y), glm::vec3(0, 0, -1) };
	m_vertices[i++] = { glm::vec3(-0.5f, -0.5, -0.5),  glm::vec2(1 - halfPixel.x,0.5 - halfPixel.y), glm::vec3(0, 0, -1) };

	// rechts
	m_vertices[i++] = { glm::vec3(0.5f, 0.5, -0.5),  glm::vec2(0.5 - halfPixel.x,0.5 + halfPixel.y), glm::vec3(1, 0, 0) };
	m_vertices[i++] = { glm::vec3(0.5f, 0.5, 0.5), glm::vec2(0 + halfPixel.x,0.5 + halfPixel.y), glm::vec3(1, 0, 0) };
	m_vertices[i++] = { glm::vec3(0.5f, -0.5, 0.5), glm::vec2(0 + halfPixel.x,0.75 - halfPixel.y), glm::vec3(1, 0, 0) };
	m_vertices[i++] = { glm::vec3(0.5f, -0.5, -0.5), glm::vec2(0.5 - halfPixel.x,0.75 - halfPixel.y), glm::vec3(1, 0, 0) };

	// unten
	m_vertices[i++] = { glm::vec3(0.5f, -0.5, 0.5), glm::vec2(0 + halfPixel.x,1 - halfPixel.y), glm::vec3(0, -1, 0) };
	m_vertices[i++] = { glm::vec3(-0.5f, -0.5, 0.5), glm::vec2(0.5 - halfPixel.x,1 - halfPixel.y), glm::vec3(0, -1, 0) };
	m_vertices[i++] = { glm::vec3(-0.5f, -0.5, -0.5), glm::vec2(0.5 - halfPixel.x,0.75 + halfPixel.y), glm::vec3(0, -1, 0) };
	m_vertices[i++] = { glm::vec3(0.5f, -0.5, -0.5), glm::vec2(0 + halfPixel.x,0.75 + halfPixel.y), glm::vec3(0, -1, 0) };

	// hinten
	m_vertices[i++] = { glm::vec3(0.5f, 0.5, 0.5), glm::vec2(1 - halfPixel.x,0.5 + halfPixel.y) , glm::vec3(0, 0, 1) };
	m_vertices[i++] = { glm::vec3(-0.5f, 0.5, 0.5), glm::vec2(0.5 + halfPixel.x,0.5 + halfPixel.y) , glm::vec3(0, 0, 1) };
	m_vertices[i++] = { glm::vec3(-0.5f, -0.5, 0.5), glm::vec2(0.5 + halfPixel.x,0.75 - halfPixel.y) , glm::vec3(0, 0, 1) };
	m_vertices[i++] = { glm::vec3(0.5f, -0.5, 0.5), glm::vec2(1 - halfPixel.x,0.75 - halfPixel.y) , glm::vec3(0, 0, 1) };

	// links
	m_vertices[i++] = { glm::vec3(-0.5f, 0.5, 0.5), glm::vec2(1 - halfPixel.x,0.75 + halfPixel.y), glm::vec3(-1, 0, 0) };
	m_vertices[i++] = { glm::vec3(-0.5f, 0.5, -0.5), glm::vec2(0.5 + halfPixel.x,0.75 + halfPixel.y), glm::vec3(-1, 0, 0) };
	m_vertices[i++] = { glm::vec3(-0.5f, -0.5, -0.5), glm::vec2(0.5 + halfPixel.x,1 - halfPixel.y), glm::vec3(-1, 0, 0) };
	m_vertices[i++] = { glm::vec3(-0.5f, -0.5, 0.5), glm::vec2(1 - halfPixel.x,1 - halfPixel.y), glm::vec3(-1, 0, 0) };

	i = 0;
	// oben
	for (int j = 0; j < 6; j++)
	{

		m_indices[i++] = 0 + j * 4;
		m_indices[i++] = 1 + j * 4;
		m_indices[i++] = 2 + j * 4;

		m_indices[i++] = 2 + j * 4;
		m_indices[i++] = 3 + j * 4;
		m_indices[i++] = 0 + j * 4;
	}

	
}

CPhongCube::~CPhongCube()
{
}

bool CPhongCube::Initialize()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertexCount, m_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indexCount, m_indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, sizeof(glm::vec3) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, sizeof(glm::vec4) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, col));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, sizeof(glm::vec2) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, sizeof(glm::vec3) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	m_shader = CGame::Get()->m_shaders["phong"];

	return true;
}

void CPhongCube::Update()
{
	if (glfwGetKey(CGame::Get()->GetWindow(), GLFW_KEY_LEFT))
	{
		m_rotation.x -= CGame::Get()->DeltaTime() * 60;
	}
	if (glfwGetKey(CGame::Get()->GetWindow(), GLFW_KEY_RIGHT))
	{
		m_rotation.x += CGame::Get()->DeltaTime() * 60;
	}
	if (glfwGetKey(CGame::Get()->GetWindow(), GLFW_KEY_DOWN))
	{
		m_rotation.y -= CGame::Get()->DeltaTime() * 60;
	}
	if (glfwGetKey(CGame::Get()->GetWindow(), GLFW_KEY_UP))
	{
		m_rotation.y += CGame::Get()->DeltaTime() * 60;
	}
}

void CPhongCube::Render()
{
	m_shader->Use();
	m_modelMatrix = glm::mat4(1);
	m_modelMatrix = glm::translate(m_modelMatrix, m_position);
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
	m_modelMatrix = glm::scale(m_modelMatrix, m_scale);

	m_shader->SetMatrix("model", m_modelMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_mainTexture);
	m_shader->SetInt("mainTex", 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_normalTexture);
	m_shader->SetInt("normalTex", 1);

	// Shader benutzung vorbereiten
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
}
