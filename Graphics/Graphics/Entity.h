#pragma once
#include "Vertex.h"
#include "Shader.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class CEntity
{
public:
	CEntity(glm::vec3 _pos);
	virtual ~CEntity();

	virtual bool Initialize();	// Erzeugen der Buffer
	virtual void Update();		// Logikupdates, zb Objekt verschieben, auf Tastendruck reagieren
	virtual void Render() = 0;	// Kommunikation mit der Grafikkarte
	virtual void CleanUp();

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	unsigned int m_VBO = 0;   // Vertex Buffer Object
	unsigned int m_VAO = 0;   // Vertex Array Object
	unsigned int m_EBO = 0;   // Element Buffer Object (Indexbuffer)

	

protected:
	Vertex* m_vertices;
	unsigned int* m_indices;

	unsigned int m_vertexCount;
	unsigned int m_indexCount;

	CShader* m_shader;

	glm::mat4 m_modelMatrix;
};

