#version 450 core
precision highp float;
layout (location = 0) in vec4 vPos;
layout (location = 1) in vec2 vTexCoord;
uniform mat4 uModelMatrix;
uniform mat4 uOrthoModelMatrix;
out vec2 TexCoord;
out vec3 modelUV;
void main()
{
	vec4 modelPos = uModelMatrix * vPos;
	TexCoord = vTexCoord;
	modelUV = vec3(vPos.x, vPos.y, vPos.z);
	gl_Position = uOrthoModelMatrix * vPos;
}