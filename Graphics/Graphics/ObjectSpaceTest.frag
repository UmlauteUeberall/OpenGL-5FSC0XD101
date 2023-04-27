#version 460 core

// Input vom Vertex Shader
in vec3 ourObjectPos;
in vec3 ourWorldPos;
in vec3 ourCameraPos;
in vec3 ourScreenPos;


// Ausgabe auf den Bildschirm (Tiefentests/Blending für Transparenz)
out vec4 FragColor;

uniform int Mode;

// Mit uniform Variablen können einzelne Variablen an alle Vertices/Pixel in einem Objekt übergeben werden


void main()
{
	if (Mode == 0)
	{
		FragColor = vec4(mod(ourObjectPos.x, 1.0), mod(ourObjectPos.y, 1.0), mod(ourObjectPos.z, 1.0), 1);
	}
	else if (Mode == 1)
	{
		FragColor = vec4(mod(ourWorldPos.x, 1.0), mod(ourWorldPos.y, 1.0), mod(ourWorldPos.z, 1.0), 1);
	}
	else if (Mode == 2)
	{
		FragColor = vec4(mod(ourCameraPos.x, 1.0), mod(ourCameraPos.y, 1.0), mod(ourCameraPos.z, 1.0), 1);
	}
	else
	{
		FragColor = vec4(mod(ourScreenPos.x, 1.0), mod(ourScreenPos.y, 1.0), mod(ourScreenPos.z, 1.0), 1);
	}
	//FragColor = vec4(texture(tex1, ourUV).rgb * ourColor * extraColor,1);
	//FragColor = vec4(ourColor, 1);
}