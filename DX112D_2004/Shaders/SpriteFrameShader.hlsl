cbuffer Frame : register(b0)
{
    float2 maxFrame;    
}

Texture2D map : register(t0);
SamplerState samp : register(s0);

struct PixelInput
{
    float4 pos : SV_Position;
    float2 uv : UV;
    float2 frame : FRAME;
};

float4 PS(PixelInput input) : SV_TARGET
{
    float2 uv;
    uv.x = (input.uv.x / maxFrame.x) + (input.frame.x / maxFrame.x);
    uv.y = (input.uv.y / maxFrame.y) + (input.frame.y / maxFrame.y);
    
    return map.Sample(samp, uv);
}