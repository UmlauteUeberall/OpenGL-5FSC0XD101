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
