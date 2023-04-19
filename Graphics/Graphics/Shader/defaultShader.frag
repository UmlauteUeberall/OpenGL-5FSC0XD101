#version 460 core

// Input vom Vertex Shader
in vec3 ourColor;
in vec2 ourUV;

// Ausgabe auf den Bildschirm (Tiefentests/Blending für Transparenz)
out vec4 FragColor;

// Mit uniform Variablen können einzelne Variablen an alle Vertices/Pixel in einem Objekt übergeben werden
uniform float textureBlend;
uniform vec2 uvZoom;

uniform sampler2D tex1;
uniform sampler2D tex2;


void main()
{
	FragColor = mix(texture(tex1, ourUV / uvZoom), texture(tex2, ourUV * uvZoom), textureBlend);
	//FragColor = vec4(texture(tex1, ourUV).rgb * ourColor * extraColor,1);
	//FragColor = vec4(ourColor, 1);
}