#version 460 core

// Daten die pro Vertex reinkommen
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 aNormal;

// Weitergabe an den Fragment Shader
out vec3 ourColor;
out vec2 ourUV;
out vec3 ourNormal;
out vec3 ourWorldPos;

uniform sampler2D heightMap;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	ourWorldPos = (model * vec4(aPos, 1)).xyz;
	float delta = texture(heightMap, aUV).r;
	ourWorldPos.y += delta * 10;

	gl_Position = projection * view * vec4(ourWorldPos, 1.0); // Mit 1 erweiten für Positionen
	ourNormal = (model * vec4(aNormal, 0)).xyz; // Lichtberechnungen immer im Worldspace, Mit 0 erweitern für Richtungen
	ourColor = aColor;
	ourUV = aUV;
}