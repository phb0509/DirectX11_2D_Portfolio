struct VertexInput
{
    float4 pos : Position;
    float2 size : Size;
};

struct VertexOutput
{
    float3 pos : Position;
    float2 size : Size;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.pos = input.pos.xyz;
    output.size = input.size;
    
    return output;
}