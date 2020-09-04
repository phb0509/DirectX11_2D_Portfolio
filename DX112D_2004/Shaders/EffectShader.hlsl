cbuffer Action : register(b0)
{
    float2 startPos;
    float2 size;
    float2 maxSize;
}

cbuffer Color : register(b1)
{
    float4 color;
}

Texture2D map : register(t0);
SamplerState samp : register(s0);

struct PixelInput
{
    float4 pos : SV_Position;
    float2 uv : UV;
};

float4 PS(PixelInput input) : SV_TARGET
{
    float2 uv = (startPos / maxSize) + input.uv * (size / maxSize);
    
    return map.Sample(samp, uv) * color;
}