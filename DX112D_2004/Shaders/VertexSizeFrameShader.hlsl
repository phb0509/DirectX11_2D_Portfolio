struct VertexInput
{
    float4 pos : Position;
    float2 size : Size;
    float2 frame : FRAME;
};

struct VertexOutput
{
    float3 pos : Position;
    float2 size : Size;
    float2 frame : FRAME;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.pos = input.pos.xyz;
    output.size = input.size;
    output.frame = input.frame;
    
    return output;
}