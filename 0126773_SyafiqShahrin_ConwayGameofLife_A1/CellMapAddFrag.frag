#version 450 core
precision highp float;
uniform float wHeight;
uniform float wWidth;
uniform float mouseX;
uniform float mouseY;
uniform float Dimension;
uniform sampler2D Main_Tex;
uniform sampler2D Main_Tex2;
uniform sampler2D Main_Tex3;
out vec4 FragColor;
in vec2 TexCoord;
in vec3 modelUV;


void main()
{
	vec4 aliveCellCol = vec4(219.0/255.0, 188.0/255.0, 33.0/255.0, 1.0);
	vec4 tex1 = texture2D(Main_Tex, TexCoord); //write texture
	vec4 tex2 = texture2D(Main_Tex2, TexCoord); //erase texture
	vec4 tex3 = texture2D(Main_Tex3, TexCoord); //read texture

	//combine write texture with read texture
	if(tex3.rgb ==  vec3(0.0) && tex1.rgb ==  vec3(1.0))
	{
		FragColor = tex1;
	}
	else
	{
		if(tex3 ==  aliveCellCol && tex1 == aliveCellCol)
		{
			FragColor = tex1;
		}
		else
		{
			FragColor = tex1 * tex3;
		}
		
		if(tex2 == aliveCellCol)
		{
			FragColor = vec4(1.0, 1.0, 1.0, 1.0);
		}
	}

}


