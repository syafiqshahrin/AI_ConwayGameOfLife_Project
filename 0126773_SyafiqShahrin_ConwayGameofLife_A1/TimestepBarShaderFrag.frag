#version 450 core
uniform sampler2D Main_Tex;
uniform float Percentage;
out vec4 FragColor;
in vec2 TexCoord;
void main()
{
	
	vec3 barCol = vec3(219.0/255.0, 188.0/255.0, 33.0/255.0);
	FragColor = vec4(0.0, 0.0, 0.0,1.0);
	vec4 borderColor = vec4(1.0, 1.0, 1.0,1.0);
	/*
	if(Percentage >= 0.5 && Percentage <= 0.7)
	{	
		barCol = vec3(1.0, 1.0, 0.0);
	}else if(Percentage >= 0.7)
	{
		barCol = vec3(1.0, 0.0, 0.0);
	}
	*/
	float border = step(0.025, TexCoord.x);
	border *= step(TexCoord.x, 1.0 - 0.025);
	border *= step(0.09, TexCoord.y);
	border *= step(TexCoord.y, 1.0 - 0.09);

	float barMin = 0.04;
	float barMax = 0.96;
	float barCurrent = (barMax - barMin) * Percentage + barMin;

	float bar = step(barMin, TexCoord.x) * step(TexCoord.x, barCurrent);
	bar *= step(0.15, TexCoord.y);
	bar *= step(TexCoord.y, 1.0 - 0.15);

	borderColor.rgb *= border;
	if(borderColor.rgb == vec3(1.0) && (bar * barCol.rgb) == barCol.rgb)
	{
		FragColor.rgb = barCol.rgb;
	}
	else if(borderColor.rgb == vec3(1.0))
	{
		FragColor.a = 0.0;
	}

	//FragColor.rgb += borderColor.rgb;
	//FragColor.rgb += (bar * barCol);

	
	
}