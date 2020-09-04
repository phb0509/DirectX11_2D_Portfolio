Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer Range : register(b1)
{
    int range;
}

cbuffer Info : register(b2)
{
    float2 imageSize;
    float2 lightPos;
}

struct PixelInput
{
    float4 pos : SV_Position;
    float2 uv : UV;
};

float4 PS(PixelInput input) : SV_TARGET
{
    float4 result = map.Sample(samp, input.uv);
    
    float2 pixelCoord = input.uv * imageSize;
    
    float dist = distance(pixelCoord, lightPos);
    
    float3 color = result.rgb - dist / range;
    
    return float4(color, result.a);
}