#version 460 core

// Input vom Vertex Shader
in vec3 ourColor;

// Ausgabe auf den Bildschirm (Tiefentests/Blending für Transparenz)
out vec4 FragColor;

void main()
{
	FragColor = vec4(ourColor,1);
}