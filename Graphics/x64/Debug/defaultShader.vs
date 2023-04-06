#version 460 core

// Daten die pro Vertex reinkommen
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

// Weitergabe an den Fragment Shader
out vec3 ourColor;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
}