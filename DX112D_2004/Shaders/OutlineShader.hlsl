//OutlineShader
Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer Color : register(b0)
{
    float4 color;
}

cbuffer Value : register(b1)
{
    int value;
    int range;
}

cbuffer Info : register(b2)
{
    float2 imageSize;    
}

struct PixelInput
{
    float4 pos : SV_Position;
    float2 uv : UV;
};

float4 Outline(float2 uv)
{
    float count = 0;
    
    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            float2 offset = (float2(x, y) / imageSize) * range;
            float4 result = map.Sample(samp, uv + offset);
            
            count += result.a;
        }
    }

    if(count > value && count < 9 - value)
        return color;    
    
    return map.Sample(samp, uv);
}

float4 PS(PixelInput input) : SV_TARGET
{
    return Outline(input.uv);
}