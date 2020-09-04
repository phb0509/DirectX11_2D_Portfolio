//FilterShader
Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer Info : register(b1)
{
    int selected;
    int value;
    int value1;
    int value2;
}

cbuffer ImageSize : register(b2)
{
    float2 imageSize;
}

struct PixelInput
{
    float4 pos : SV_Position;
    float2 uv : UV;
};

float4 Mosaic(float2 uv)
{
    //int x = (int) (uv.x * value);
    //int y = (int) (uv.y * value);
    
    float x = floor(uv.x * value);
    float y = floor(uv.y * value);
    
    float2 temp;
    temp.x = x / value;
    temp.y = y / value;
    
    return map.Sample(samp, temp);
}

float4 Blur(float2 uv)
{
    float4 result = 0;
            
    for (int i = 0; i < value; i++)
    {    
        float divX = (i + 1) / imageSize.x;
        float divY = (i + 1) / imageSize.y;
        
        result += map.Sample(samp, float2(uv.x + divX, uv.y));
        result += map.Sample(samp, float2(uv.x - divX, uv.y));
        result += map.Sample(samp, float2(uv.x, uv.y + divY));
        result += map.Sample(samp, float2(uv.x, uv.y - divY));
    }
    
    result /= 4 * value;
    
    return result;
}

static const float2 edges[8] =
{
    float2(-1, -1), float2(0, -1), float2(1, -1),
    float2(-1, 0), float2(1, 0),
    float2(-1, 1), float2(0, 1), float2(1, 1),
};

float4 OctaBlur(float2 uv)
{
    float4 result = 0;
    //[unroll(4)]    
    for (int i = 0; i < value; i++)
    {
        float divX = (i + 1) / imageSize.x;
        float divY = (i + 1) / imageSize.y;
        
        for (int j = 0; j < 8; j++)
        {
            float x = edges[j].x * divX + uv.x;
            float y = edges[j].y * divY + uv.y;
            
            result += map.Sample(samp, float2(x, y));
        }
    }
    
    result /= 8 * value;
    
    return result;
}

static const float weights[13] =
{
    0.0561f, 0.1353f, 0.2730f, 0.4868f, 0.7261f, 0.9231f,
    1.0f,
    0.9231f, 0.7261f, 0.4868f, 0.2730f, 0.1353f, 0.0561f
};

float4 GaussianBlur(float2 uv)
{
    float divX = 1.0f / imageSize.x;
    float divY = 1.0f / imageSize.y;
    
    float sum = 0;
    float4 result = 0;
    
    for (int i = -6; i <= 6; i++)
    {
        float2 temp = uv + float2(divX * i * value, 0);
        result += weights[6 + i] * map.Sample(samp, temp);
        
        temp = uv + float2(0, divY * i * value);
        result += weights[6 + i] * map.Sample(samp, temp);
        
        sum += weights[6 + i] * 2;
    }

    result /= sum;
    
    return result;
}

float4 RadialBlur(float2 uv)
{
    float2 radiusUV = uv - float2(0.5f, 0.5f);
    float r = length(radiusUV);
    radiusUV /= r;
    
    r = saturate(2 * r / value1);
    
    float2 delta = -radiusUV * r * r * value2 / value;
    
    float4 result = 0;
    
    for (int i = 0; i < value; i++)
    {
        result += map.Sample(samp, uv);
        uv += delta;
    }

    result /= value;
    
    return result;
}

float4 Outline(float2 uv)
{
    float4 result = map.Sample(samp, uv);
    
    if(result.a > 0.0f && result.a < 1.0f)
        return float4(1, 0, 0, 1);
    
    return result;
}

float4 PS(PixelInput input) : SV_TARGET
{
    [branch]
    if(selected == 1)
        return Mosaic(input.uv);
    else if(selected == 2)
        return Blur(input.uv);
    else if (selected == 3)
        return OctaBlur(input.uv);
    else if (selected == 4)
        return GaussianBlur(input.uv);
    else if (selected == 5)
        return RadialBlur(input.uv);
    else if (selected == 6)
        return Outline(input.uv);
    
    return map.Sample(samp, input.uv);
}