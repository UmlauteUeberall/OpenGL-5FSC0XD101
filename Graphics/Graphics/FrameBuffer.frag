#version 460 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
	FragColor = vec4(texture(screenTexture, TexCoords).rgb, 1);
	
	//FragColor = vec4(vec3(1,1,1) - FragColor.rgb, 1);// Farben invertieren
	
	//FragColor = vec4(texture(screenTexture, vec2(1,1) - TexCoords).rgb, 1); // Spiegel das Bild um den Mittelpunkt

	float average = (FragColor.r + FragColor.g + FragColor.b) / 3;
	vec4 averageCol = vec4(average, average, average, 1); 
	FragColor = mix(FragColor, averageCol, TexCoords.y);
}
