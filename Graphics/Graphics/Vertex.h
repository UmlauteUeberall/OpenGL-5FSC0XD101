#pragma once
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>

struct Vertex
{
	glm::vec3 pos;
	glm::vec4 col;
	glm::vec2 uv;
	glm::vec3 normal;

	Vertex()
	{
		pos = glm::vec3(0, 0, 0);
		col = glm::vec4(1, 1, 1, 1);
		uv = glm::vec2(0, 0);
		normal = glm::vec3(0,0,0);
	}

	Vertex(glm::vec3 _position, glm::vec3 _normal)
	{
		pos = _position;
		col = glm::vec4(1, 1, 1, 1);
		uv = glm::vec2(0, 0);
		normal = _normal;
	}

	Vertex(glm::vec3 _position, glm::vec4 _color, glm::vec2 _uv)
	{
		pos = _position;
		col = _color;
		uv = _uv;
		normal = glm::vec3(0,0,0);
	}

	Vertex(glm::vec3 _position, glm::vec4 _color, glm::vec2 _uv, glm::vec3 _normal)
	{
		pos = _position;
		col = _color;
		uv = _uv;
		normal = _normal;
	}

	Vertex(glm::vec3 _position, glm::vec2 _uv, glm::vec3 _normal)
	{
		pos = _position;
		col = glm::vec4(1,1,1,1);
		uv = _uv;
		normal = _normal;
	}
};
