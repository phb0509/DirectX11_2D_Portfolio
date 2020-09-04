Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer Color : register(b0)
{
    float4 color : COLOR;
}

cbuffer Int : register(b1)
{
    int selected : SELECTED;
}

struct PixelInput
{
    float4 pos : SV_Position;
    float2 uv : UV;
};

float4 Grayscale(float4 albedo)
{
    //float scale = (color.r + color.g + color.b) / 3;
    
    //float3 grayColor;
    //grayColor.r = color.r * 0.3f;
    //grayColor.g = color.g * 0.59f;
    //grayColor.b = color.b * 0.11f;
    
    //float scale = grayColor.r + grayColor.g + grayColor.b;
    
    float scale = dot(albedo.rgb, float3(0.3f, 0.59f, 0.11f));
    
    return float4(scale.xxx, albedo.a) * color;
}

float4 Sepia(float4 albedo)
{
    float4 sepia;
    
    sepia.a = albedo.a;
    
    sepia.r = dot(albedo.rgb, float3(0.393f, 0.769f, 0.189f));
    sepia.g = dot(albedo.rgb, float3(0.349f, 0.686f, 0.168f));
    sepia.b = dot(albedo.rgb, float3(0.272f, 0.534f, 0.131f));
    
    return sepia * color;
}

float4 PS(PixelInput input) : SV_TARGET
{
    float4 albedo = map.Sample(samp, input.uv);
    
    if(selected == 1)
        return Grayscale(albedo);
    else if(selected == 2)
        return Sepia(albedo);    
    
    return albedo;
}