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

	m_shader = CGame::Get()->m_defaultShader;

    return true;
}

void CEntity::Update()
{
	m_rotation.x += CGame::Get()->DeltaTime() * 13;
	m_rotation.z += CGame::Get()->DeltaTime() * 30;
}

void CEntity::Render()
{
	m_modelMatrix = glm::mat4(1);
	m_modelMatrix = glm::translate(m_modelMatrix, m_position);
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.z), glm::vec3(0,0,1));
	m_modelMatrix = glm::scale(m_modelMatrix, m_scale);

	m_shader->SetMatrix("model", m_modelMatrix);

	// Variablen setzen
	m_shader->SetFloat("textureBlend", sin(glfwGetTime()) / 2.0f + 0.5f);
	m_shader->SetVector2("uvZoom", glm::vec2(sin(glfwGetTime()) / 2.0f + 0.5f,
		cos(glfwGetTime() * 0.23) * 2));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture1);
	m_shader->SetInt("tex1", 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture2);
	m_shader->SetInt("tex2", 1);

	// Shader benutzung vorbereiten
	m_shader->Use();
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
}

void CEntity::CleanUp()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}
