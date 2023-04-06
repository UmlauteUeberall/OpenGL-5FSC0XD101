#pragma once
#include "Vector.h"

struct Vertex
{
	Vector3 pos;
	Vector3 col;

	Vertex(Vector3 _position, Vector3 _color)
	{
		pos = _position;
		col = _color;
	}
};
