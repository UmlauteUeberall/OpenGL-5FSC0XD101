#include "Entity.h"
#include "Game.h"


CEntity::CEntity(glm::vec3 _pos)
{
    m_position = _pos;
	m_scale = glm::vec3(1, 1, 1);
}

CEntity::~CEntity()
{
}

bool CEntity::Initialize()
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

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	m_shader = CGame::Get()->m_shaders["default"];

    return true;
}

void CEntity::Update()
{
	m_rotation.x += CGame::Get()->DeltaTime() * 13;
	m_rotation.z += CGame::Get()->DeltaTime() * 30;
}

void CEntity::CleanUp()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}
