cbuffer Color : register(b0)
{
    float4 color;
}

struct PixelInput
{
    float4 pos : SV_Position;
    float2 uv : UV;
};

float4 PS(PixelInput input) : SV_TARGET
{
    return color;
}