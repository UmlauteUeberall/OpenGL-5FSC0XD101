#include "ObjectSpaceCube.h"
#include "Game.h"

CObjectSpaceCube::CObjectSpaceCube(glm::vec3 _pos)
	:CEntity(_pos)
{
	m_vertexCount = 8;
	m_indexCount = 36;

	m_vertices = new Vertex[m_vertexCount];
	m_indices = new unsigned int[m_indexCount];

	int i = 0;
	m_vertices[i++] = { glm::vec3(-0.5f, 0.5, 0.5), glm::vec4(0.882f, 0.0313f, 0.91f,1), glm::vec2(0,0) };
	m_vertices[i++] = { glm::vec3(0.5f, 0.5, 0.5), glm::vec4(1,0,0,1), glm::vec2(1,0) };
	m_vertices[i++] = { glm::vec3(0.5f, 0.5, -0.5), glm::vec4(1,1,0,1), glm::vec2(1,1) };
	m_vertices[i++] = { glm::vec3(-0.5f, 0.5, -0.5), glm::vec4(0.2f,0.49f,0.82f, 1), glm::vec2(0,1) };

	m_vertices[i++] = { glm::vec3(-0.5f, -0.5, 0.5), glm::vec4(0.882f, 1, 0.91f,1), glm::vec2(1,1) };
	m_vertices[i++] = { glm::vec3(0.5f, -0.5, 0.5), glm::vec4(1,0,1,1),  glm::vec2(0,1) };
	m_vertices[i++] = { glm::vec3(0.5f, -0.5, -0.5), glm::vec4(0,0,1,1), glm::vec2(0,0) };
	m_vertices[i++] = { glm::vec3(-0.5f, -0.5, -0.5), glm::vec4(0.5f,0.49f,0.82f, 1), glm::vec2(1,0) };

	i = 0;
	// oben
	m_indices[i++] = 0;
	m_indices[i++] = 1;
	m_indices[i++] = 2;

	m_indices[i++] = 2;
	m_indices[i++] = 3;
	m_indices[i++] = 0;

	// vorne
	m_indices[i++] = 3;
	m_indices[i++] = 2;
	m_indices[i++] = 7;

	m_indices[i++] = 2;
	m_indices[i++] = 6;
	m_indices[i++] = 7;

	// rechts
	m_indices[i++] = 2;
	m_indices[i++] = 1;
	m_indices[i++] = 5;

	m_indices[i++] = 5;
	m_indices[i++] = 6;
	m_indices[i++] = 2;

	// hinten
	m_indices[i++] = 1;
	m_indices[i++] = 0;
	m_indices[i++] = 4;

	m_indices[i++] = 4;
	m_indices[i++] = 5;
	m_indices[i++] = 1;

	// links
	m_indices[i++] = 3;
	m_indices[i++] = 7;
	m_indices[i++] = 4;

	m_indices[i++] = 4;
	m_indices[i++] = 0;
	m_indices[i++] = 3;

	// unten
	m_indices[i++] = 4;
	m_indices[i++] = 7;
	m_indices[i++] = 6;

	m_indices[i++] = 6;
	m_indices[i++] = 5;
	m_indices[i++] = 4;

}

CObjectSpaceCube::~CObjectSpaceCube()
{
}

bool CObjectSpaceCube::Initialize()
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

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	m_shader = CGame::Get()->m_shaders["objectSpace"];

	return true;
}

void CObjectSpaceCube::Update()
{
	m_rotation.y += CGame::Get()->DeltaTime() * 10.0f;
	
	if (CGame::Get()->KeyDown(GLFW_KEY_UP))
	{
		m_Mode++;
	}
	else if (CGame::Get()->KeyDown(GLFW_KEY_DOWN))
	{
		m_Mode--;
	}

	m_Mode = (4 + m_Mode) % 4;
}

void CObjectSpaceCube::Render()
{
	m_shader->Use();
	m_modelMatrix = glm::mat4(1);
	m_modelMatrix = glm::translate(m_modelMatrix, m_position);
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
	m_modelMatrix = glm::scale(m_modelMatrix, m_scale);

	m_shader->SetMatrix("model", m_modelMatrix);
	m_shader->SetInt("Mode", m_Mode);

	// Shader benutzung vorbereiten
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
}
