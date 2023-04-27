#include "Terrain.h"
#include "Game.h"

CTerrain::CTerrain(glm::vec3 _pos, int _widthSegments, int _depthSegments)
	: CEntity(_pos)
{
	int width, height;

	m_mainTexture = CGame::Get()->LoadTexture("Terrain.jpg", &width, &height);
	m_heightMap = CGame::Get()->LoadTexture("Heightmap.jpg", &width, &height);

	m_vertexCount = (_widthSegments + 1) * (_depthSegments + 1);
	m_indexCount = _widthSegments * _depthSegments * 2 * 3;

	m_vertices = new Vertex[m_vertexCount];
	m_indices = new unsigned int[m_indexCount];

	glm::vec2 halfPixel = glm::vec2(0.5, 0.5) / glm::vec2(width, height);

	int i = 0;
	for (int z = 0; z < _depthSegments + 1; z++)
	{
		for (int x = 0; x < _widthSegments + 1; x++)
		{
			m_vertices[i++] = Vertex(glm::vec3(x, 0.0, z) * 0.2f, glm::vec2(x/ (_widthSegments - 1.0f), z / (_depthSegments - 1.0f)), glm::vec3(0, 1, 0));
		}
	}

	i = 0;

	for (int z = 0; z < _depthSegments; z++)
	{
		for (int x = 0; x < _widthSegments; x++)
		{
			m_indices[i++] = x + (z * (_widthSegments + 1));
			m_indices[i++] = x + ((z + 1) * (_widthSegments + 1));
			m_indices[i++] = x + (z * (_widthSegments + 1)) + 1;

			m_indices[i++] = x + (z * (_widthSegments + 1)) + 1;
			m_indices[i++] = x + ((z + 1) * (_widthSegments + 1));
			m_indices[i++] = x + ((z + 1) * (_widthSegments + 1)) + 1;
		}
	}
}

CTerrain::~CTerrain()
{
}

bool CTerrain::Initialize()
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

	m_shader = CGame::Get()->m_shaders["terrain"];

	return true;
}

void CTerrain::Update()
{
}

void CTerrain::Render()
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
	glBindTexture(GL_TEXTURE_2D, m_heightMap);
	m_shader->SetInt("heightMap", 1);

	// Shader benutzung vorbereiten
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
}
