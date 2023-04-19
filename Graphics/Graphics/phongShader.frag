#version 460 core

// Input vom Vertex Shader
in vec3 ourColor;
in vec2 ourUV;
in vec3 ourNormal;
in vec3 ourWorldPos;

// Ausgabe auf den Bildschirm (Tiefentests/Blending f�r Transparenz)
out vec4 FragColor;

// Mit uniform Variablen k�nnen einzelne Variablen an alle Vertices/Pixel in einem Objekt �bergeben werden
uniform vec3 AmbientColor;
uniform vec3 DiffuseColor;
uniform vec3 LightDir;
uniform vec3 SpecularColor;
uniform vec3 CameraPos;

void main()
{
	// Grundhelligkeit, Deutlich g�nstiger als alles zu Raytracen
	// Color
	vec3 ambientLight = clamp(ourColor * AmbientColor,0,1);
	// Direkte Beleuchtung eines Objektes
	// Color, Lichtrichtung, Oberfl�chenrichtung
	// dot -	Punktprodukt gibt den Winkel zwischen zwei Vektoren an, 
	//			vorteilhaft zu normalisieren vorher dann gibt es Wertebereich -1 - 1
	// cross -	Krezprodukt gibt einen Vektor aus der im rechten Winkel zu beiden Inputs steht
	//			Seine L�nge ist die Fl�che des aufgespannten Parellelograms
	vec3 diffuseLight = clamp(ourColor * 
							DiffuseColor * 
							dot(normalize(-LightDir), normalize(ourNormal)), 
						0, 1);
	// Glanzpunkte
	// Color, Lichtrichtung, Oberfl�chenrichtung, Camerapos
	vec3 halfVector = normalize(normalize(CameraPos - ourWorldPos) + normalize(-LightDir));
	float dotP = dot(halfVector, normalize(ourNormal));
	dotP = pow(dotP, 100);
	vec3 specularLight = clamp(SpecularColor * dotP, 0, 1);

	FragColor = vec4(ambientLight + diffuseLight + specularLight, 1);
}