cbuffer View : register(b1)
{
    matrix view;
}

cbuffer Projection : register(b2)
{
    matrix projection;
}

struct GeometryInput
{
	float3 pos : Position;
    float2 size : Size;
};

struct GeometryOutput
{
    float4 pos : SV_Position;
    float2 uv : UV;
};

static const float2 TEXCOORD[4] =
{
    float2(0.0f, 1.0f),
    float2(0.0f, 0.0f),
    float2(1.0f, 1.0f),
    float2(1.0f, 0.0f)
};

[maxvertexcount(4)]
void GS(point GeometryInput input[1], 
	inout TriangleStream< GeometryOutput > stream)
{
    float3 right = { 1, 0, 0 };
    float3 up = { 0, 1, 0 };
	
    float halfWidth = input[0].size.x * 0.5f;
    float halfHeight = input[0].size.y * 0.5f;
	
    float4 vertices[4];
    vertices[0] = float4(input[0].pos - halfWidth * right - halfHeight * up, 1);
    vertices[1] = float4(input[0].pos - halfWidth * right + halfHeight * up, 1);    
    vertices[2] = float4(input[0].pos + halfWidth * right - halfHeight * up, 1);    
    vertices[3] = float4(input[0].pos + halfWidth * right + halfHeight * up, 1);
    
    GeometryOutput output;
	
	for (uint i = 0; i < 4; i++)
	{        
        output.pos = mul(vertices[i], view);
        output.pos = mul(output.pos, projection);
        
        output.uv = TEXCOORD[i];
        
		stream.Append(output);
	}
}
