#version 450 core
precision highp float;
uniform float wHeight;
uniform float wWidth;
uniform float mouseX;
uniform float mouseY;
uniform float Dimension;
uniform int Clicked;
uniform sampler2D Main_Tex;
out vec4 FragColor;
in vec2 TexCoord;
in vec3 modelUV;


void main()
{
    
	FragColor = texture2D(Main_Tex, TexCoord);
	//FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    

}


