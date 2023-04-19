#include "Quad.h"
#include "Game.h"

CQuad::CQuad(glm::vec3 _pos)
	: CEntity(_pos)
{
	m_vertexCount = 4;
	m_indexCount = 6;

	m_vertices = new Vertex[m_vertexCount];
	m_indices = new unsigned int[m_indexCount];

	int i = 0;
	m_vertices[i++] = { glm::vec3(-0.5f, 0.5, 0.0), glm::vec4(0.882f, 0.0313f, 0.91f,1), glm::vec2(0,0) };
	m_vertices[i++] = { glm::vec3(0.5f, 0.5, 0.0), glm::vec4(1,0,0,1), glm::vec2(1,0) };
	m_vertices[i++] = { glm::vec3(0.5f, -0.5, 0.0), glm::vec4(1,1,0,1), glm::vec2(1,1) };
	m_vertices[i++] = { glm::vec3(-0.5f, -0.5, 0.0), glm::vec4(0.2f,0.49f,0.82f, 1), glm::vec2(0,1) };

	i = 0;
	m_indices[i++] = 0;
	m_indices[i++] = 1;
	m_indices[i++] = 3;

	m_indices[i++] = 1;
	m_indices[i++] = 2;
	m_indices[i++] = 3;

	m_texture1 = CGame::Get()->LoadTexture("Test.jpg");
	m_texture2 = CGame::Get()->LoadTexture("Smiley2.png");
}

CQuad::~CQuad()
{
}

void CQuad::Render()
{
	m_shader->Use();
	m_modelMatrix = glm::mat4(1);
	m_modelMatrix = glm::translate(m_modelMatrix, m_position);
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
	m_modelMatrix = glm::scale(m_modelMatrix, m_scale);

	m_shader->SetMatrix("model", m_modelMatrix);

	// Variablen setzen
	m_shader->SetFloat("textureBlend", sin(glfwGetTime() * 0.23f) / 2.0f + 0.5f);
	m_shader->SetVector2("uvZoom", glm::vec2(sin(glfwGetTime() * 0.1f) / 2.0f + 0.5f,
		cos(glfwGetTime() * 0.23) * 2));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture1);
	m_shader->SetInt("tex1", 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture2);
	m_shader->SetInt("tex2", 1);

	// Shader benutzung vorbereiten
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
}
