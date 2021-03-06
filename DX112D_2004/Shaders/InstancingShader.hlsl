cbuffer World : register(b0)
{
    matrix world;
}

cbuffer View : register(b1)
{
    matrix view;
}

cbuffer Projection : register(b2)
{
    matrix projection;
}

struct VertexInput
{
    float4 pos : Position;
    float2 uv : UV;
    
    matrix transform : Instance;
    uint instanceID : SV_InstanceID;
};

struct VertexOutput
{
    float4 pos : SV_Position;
    float2 uv : UV;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.pos = mul(input.pos, input.transform);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    output.uv = input.uv;
    
    return output;
}