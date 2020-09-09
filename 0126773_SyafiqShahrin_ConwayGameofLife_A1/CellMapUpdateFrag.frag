#version 450 core
precision highp float;
uniform float wHeight;
uniform float wWidth;
uniform float mouseX;
uniform float mouseY;
uniform float Dimension;
uniform sampler2D Main_Tex;
out vec4 FragColor;
in vec2 TexCoord;
in vec3 modelUV;


int CheckAliveNeighbours(vec2 nUVRaw)
{

	vec4 aliveCellCol = vec4(219.0/255.0, 188.0/255.0, 33.0/255.0, 1.0);
	// Vector to check:
	// (1,0) right
	// (1,1) right up
	// (0,1) up
	// (-1,1) left up
	// (-1,0) left
	// (-1,-1) left down
	// (0, -1) down
	// (1, -1) right down
	int aliveNeighbours = 0;
	for(float y = -1.0; y < 2.0; y+=1.0)
	{
		for(float x = -1.0; x < 2.0; x+=1.0)
		{
			vec2 testUV = vec2(nUVRaw.x + x, nUVRaw.y + y);
			testUV /= Dimension;
			vec2 UV2 = vec2(testUV.x / (wWidth/wHeight) , testUV.y);
			vec4 sampleCell = texture2D(Main_Tex, UV2);
			float boundary = Dimension * (wWidth/wHeight);
			if( testUV.x > boundary || testUV.y > boundary || testUV.x < 0.0 || testUV.y < 0.0)
			{
				continue;
			}
			if(x == 0.0 && y == 0.0)
			{
				continue;
			}
			else
			{
	
				if(sampleCell == aliveCellCol)
				{
					aliveNeighbours += 1;
				}
				
			}
				
		}
	}
	return aliveNeighbours;
}

void main()
{
	vec4 aliveCellCol = vec4(219.0/255.0, 188.0/255.0, 33.0/255.0, 1.0);
	vec4 deadCellCol = vec4(1.0);
    vec4 col = vec4(0.0, 0.0, 0.0, 1.0);

	vec2 nUV = vec2(TexCoord.x * (wWidth/wHeight), TexCoord.y);
	nUV *= Dimension;
	vec2 nUVRaw = nUV;
	nUV = fract(nUV);

	
	
	
	vec4 currentTexCol = texture2D(Main_Tex, TexCoord);
	col = currentTexCol;
	int aliveNeighbours = CheckAliveNeighbours(nUVRaw);
	if(currentTexCol == deadCellCol)
	{
		if(aliveNeighbours == 3)
		{
			col = aliveCellCol;
		}
	}
	if(currentTexCol == aliveCellCol)
	{
		if(aliveNeighbours >= 4 || aliveNeighbours <= 1)
		{
			col = deadCellCol;
		}
		else
		{
			col = aliveCellCol;
		}
	}
	FragColor = col;
	//FragColor = texture2D(Main_Tex, TexCoord);

    

}


