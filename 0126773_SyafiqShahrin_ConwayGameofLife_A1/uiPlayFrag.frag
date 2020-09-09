#version 450 core
uniform sampler2D Main_Tex;
uniform int IsPlaying;
uniform int IsHovered;
uniform float Time;
out vec4 FragColor;
in vec2 TexCoord;
void main()
{
	vec3 color = vec3(219.0/255.0, 188.0/255.0, 33.0/255.0);
	//FragColor = vec4(vec3(1.0,0.0,0.0), 1.0);
	//FragColor = vec4(gl_FragCoord.x/800.0, gl_FragCoord.y/600.0, 0.0, 1.0);
	FragColor = texture2D(Main_Tex, TexCoord);

	if(IsHovered == 1)
	{
		
		if(FragColor.a < 0.5f)
		{
			FragColor = vec4(1.0);
			FragColor.rgb *= color;
		}
	}
	else if(IsPlaying == 1)
	{
		if(FragColor.a < 0.5f)
		{
			//float bar = smoothstep(TexCoord.x + (1.0 - fract(Time)), TexCoord.x + 0.5 +(1.0 - fract(Time)), 1.0) ;
			float bar = smoothstep(TexCoord.x + (1.0 - mod(Time, 1.1)), TexCoord.x + 0.1 +(1.0 - mod(Time, 1.1)), 1.0);
			float bar2 = smoothstep(TexCoord.x + 0.5 + (1.0 - mod(Time, 1.1)), TexCoord.x + 0.1 + (1.0 - mod(Time, 1.1)), 1.0);
			FragColor += (bar * bar2);
			FragColor.rgb *= color - ( 0.4 * color);
		}
	}

}