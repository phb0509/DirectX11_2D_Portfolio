
Texture2D map : register(t0);
SamplerState samp : register(s0);

struct VertexInput
{
    float4 pos : Position;
    float2 uv : UV;
};

struct PixelInput
{
    float4 pos : SV_Position;
    float2 uv : UV;
};

PixelInput VS(VertexInput input)
{ 
    PixelInput output;
    output.pos = input.pos;
    output.uv = input.uv;
    
    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    return map.Sample(samp, input.uv);
}