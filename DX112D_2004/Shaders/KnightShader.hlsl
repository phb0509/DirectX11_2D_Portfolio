cbuffer Action : register(b0)
{
    float2 startPos;
    float2 size;
    float2 maxSize;
}

cbuffer Value : register(b1)
{
    int value;
    int range;
    int isOutline;
}

cbuffer Color : register(b2)
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

float4 Outline(float2 uv)
{
    float count = 0;
    
    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            float2 offset = (float2(x, y) / maxSize) * (range + 1);
            float4 result = map.Sample(samp, uv + offset);
            
            count += result.a;
        }
    }

    if (count > value && count < 9 - value)
        return color;
    
    return map.Sample(samp, uv);
}

float4 PS(PixelInput input) : SV_TARGET
{
    float2 uv = (startPos / maxSize) + input.uv * (size / maxSize);
  //float2 uv = (startPos / maxSize) + input.uv * (size / maxSize);
    if(isOutline)
        return Outline(uv);
    
    return map.Sample(samp, uv);
}