//MultiShader
Texture2D map1 : register(t0);
Texture2D map2 : register(t1);

SamplerState samp : register(s0);

cbuffer Selected : register(b1)
{
    int selected;    
}

struct PixelInput
{
    float4 pos : SV_Position;
    float2 uv : UV;
};

float4 Modulate(float2 uv)
{
    float4 tex1 = map1.Sample(samp, uv);
    float4 tex2 = map2.Sample(samp, uv);
    
    return tex1 * tex2;
}

float4 Modulate2X(float2 uv)
{
    float4 tex1 = map1.Sample(samp, uv);
    float4 tex2 = map2.Sample(samp, uv);
    
    return tex1 * tex2 * 2.0f;
}

float4 Add(float2 uv)
{
    float4 tex1 = map1.Sample(samp, uv);
    float4 tex2 = map2.Sample(samp, uv);
    
    return tex1 + tex2;
}

float4 AddSmooth(float2 uv)
{
    float4 tex1 = map1.Sample(samp, uv);
    float4 tex2 = map2.Sample(samp, uv);
    
    return tex1 + tex2 - tex1 * tex2;
}

float4 AddSigned(float2 uv)
{
    float4 tex1 = map1.Sample(samp, uv);
    float4 tex2 = map2.Sample(samp, uv);
    
    return tex1 + tex2 - 0.5f;
}

float4 AddSigned2X(float2 uv)
{
    float4 tex1 = map1.Sample(samp, uv);
    float4 tex2 = map2.Sample(samp, uv);
    
    return (tex1 + tex2 - 0.5f) * 2.0f;
}

float4 Subtract(float2 uv)
{
    float4 tex1 = map1.Sample(samp, uv);
    float4 tex2 = map2.Sample(samp, uv);
    
    return float4((tex1 - tex2).rgb, 1.0f);
}

float4 RevSubtract(float2 uv)
{
    float4 tex1 = map1.Sample(samp, uv);
    float4 tex2 = map2.Sample(samp, uv);
    
    return float4((tex2 - tex1).rgb, 1.0f);
}

float4 PS(PixelInput input) : SV_TARGET
{
    if(selected == 1)
        return Modulate(input.uv);
    else if (selected == 2)
        return Modulate2X(input.uv);
    else if (selected == 3)
        return Add(input.uv);
    else if (selected == 4)
        return AddSmooth(input.uv);
    else if (selected == 5)
        return AddSigned(input.uv);
    else if (selected == 6)
        return AddSigned2X(input.uv);
    else if (selected == 7)
        return Subtract(input.uv);
    else if (selected == 8)
        return RevSubtract(input.uv);
    
    return map1.Sample(samp, input.uv);
}