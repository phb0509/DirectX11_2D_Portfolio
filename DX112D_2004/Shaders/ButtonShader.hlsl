cbuffer Frame : register(b0)
{
    float2 maxFrame;
    float2 curFrame;
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
    float2 uv;
    uv.x = (input.uv.x / maxFrame.x) + (curFrame.x / maxFrame.x);
    uv.y = (input.uv.y / maxFrame.y) + (curFrame.y / maxFrame.y);
    
    return map.Sample(samp, uv) * color;
}