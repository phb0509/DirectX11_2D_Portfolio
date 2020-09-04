cbuffer Action : register(b0)
{
    float2 startPos;
    float2 size;
    float2 maxSize;
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

    float4 result = map.Sample(samp, uv);
    
    if(result.r == 1.0f && result.b == 1.0f && result.g == 0)
        result.a = 0.0f;
    
    return result;
}