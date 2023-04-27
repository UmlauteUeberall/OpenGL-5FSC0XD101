#version 460 core

// Input vom Vertex Shader
in vec3 ourColor;
in vec2 ourUV;
in vec3 ourNormal;
in vec3 ourWorldPos;

// Ausgabe auf den Bildschirm (Tiefentests/Blending für Transparenz)
out vec4 FragColor;

// Mit uniform Variablen können einzelne Variablen an alle Vertices/Pixel in einem Objekt übergeben werden
uniform vec3 AmbientColor;
uniform vec3 DiffuseColor;
uniform vec3 LightDir;
uniform vec3 SpecularColor;
uniform vec3 CameraPos;

uniform mat4 model;

uniform sampler2D mainTex;
uniform sampler2D heightMap;

//uniform sampler2D normalTex;


void main()
{

	vec3 normal = normalize(vec3((texture(heightMap, ourUV - vec2(0.5f/512, 0)).r - texture(heightMap, ourUV + vec2(0.5f/512, 0)).r),
							0.01,
							(texture(heightMap, ourUV - vec2(0, 0.5f/512)).r - texture(heightMap, ourUV + vec2(0, 0.5f/512)).r)
		));

	vec3 colXY = texture(mainTex, ourWorldPos.xy).rgb * ourColor;
	vec3 colZY = texture(mainTex, ourWorldPos.zy).rgb * ourColor;
	vec3 colXZ = texture(mainTex, ourWorldPos.xz).rgb * ourColor;

	vec3 weight = vec3(abs(normal.x), abs(normal.y),abs(normal.z));
	weight = normalize(vec3(pow(weight.x, 10), pow(weight.y, 10), pow(weight.z, 10)));

	vec3 texColor = colXZ * weight.y + colXY * weight.z + colZY * weight.x;
	//vec3 normal = normalize((model * vec4(texture(normalTex, ourUV).rgb, 0)).rgb + normalize(ourNormal));

	// Grundhelligkeit, Deutlich günstiger als alles zu Raytracen
	// Color
	vec3 ambientLight = clamp(texColor * AmbientColor,0,1);
	// Direkte Beleuchtung eines Objektes
	// Color, Lichtrichtung, Oberflächenrichtung
	// dot -	Punktprodukt gibt den Winkel zwischen zwei Vektoren an, 
	//			vorteilhaft zu normalisieren vorher dann gibt es Wertebereich -1 - 1
	// cross -	Krezprodukt gibt einen Vektor aus der im rechten Winkel zu beiden Inputs steht
	//			Seine Länge ist die Fläche des aufgespannten Parellelograms
	vec3 diffuseLight = clamp(texColor * 
							DiffuseColor * 
							dot(normalize(-LightDir), normal), 
						0, 1);
	// Glanzpunkte
	// Color, Lichtrichtung, Oberflächenrichtung, Camerapos
	vec3 halfVector = normalize(normalize(CameraPos - ourWorldPos) + normalize(-LightDir));
	float dotP = dot(halfVector, normal);
	dotP = pow(dotP, 100);
	vec3 specularLight = clamp(SpecularColor * dotP, 0, 1) * 0.05;

	FragColor = vec4(ambientLight + diffuseLight + specularLight, 1);
}