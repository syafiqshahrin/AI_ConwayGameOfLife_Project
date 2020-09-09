#version 450 core
precision highp float;
uniform float wHeight;
uniform float wWidth;
uniform float mouseX;
uniform float mouseY;
uniform float Dimension;
out vec4 FragColor;
in vec2 TexCoord;
in vec3 modelUV;


void main()
{
	vec4 aliveCellCol = vec4(219.0/255.0, 188.0/255.0, 33.0/255.0, 1.0);
    vec3 col = vec3(0.0);
	vec2 nUV = vec2(TexCoord.x* (wWidth/wHeight), TexCoord.y);
	nUV *= Dimension;
	nUV = fract(nUV);

	float gY = step(0.1, nUV.y);
	float gX = step(0.1, nUV.x );
	float gXY = gX * gY;
	col = vec3(gXY);
	if(gXY == 1.0)
	{
		if(floor(mouseX * Dimension * (wWidth/wHeight)) == floor(TexCoord.x * Dimension * (wWidth/wHeight)) && floor(mouseY * Dimension ) == floor(TexCoord.y * Dimension))
		{
			col *= aliveCellCol.rgb;
		}
	}
	else
	{
		col = vec3(0.0);
	}
	
	FragColor = vec4(col, 1.0);

    

}


