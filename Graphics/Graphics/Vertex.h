#pragma once
#include "Vector.h"

struct Vertex
{
	Vector3 pos;
	Vector3 col;
	Vector2 uv;

	Vertex(Vector3 _position, Vector3 _color, Vector2 _uv)
	{
		pos = _position;
		col = _color;
		uv = _uv;
	}
};
