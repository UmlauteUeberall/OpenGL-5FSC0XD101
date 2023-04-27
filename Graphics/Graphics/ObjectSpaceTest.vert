#version 460 core

// Daten die pro Vertex reinkommen
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV;

// Weitergabe an den Fragment Shader
out vec3 ourObjectPos;
out vec3 ourWorldPos;
out vec3 ourCameraPos;
out vec3 ourScreenPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	ourObjectPos = aPos;
	ourWorldPos = (model * vec4(aPos, 1.0)).xyz;
	ourCameraPos = (view * model * vec4(aPos, 1.0)).xyz;
	ourScreenPos = gl_Position.xyz;
}