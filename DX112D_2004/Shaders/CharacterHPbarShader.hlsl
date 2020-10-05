Texture2D map : register(t0);
SamplerState samp : register(s0);


cbuffer Info : register(b1)
{
    float hpRate;
}

struct PixelInput
{
    float4 pos : SV_Position;
    float2 uv : UV;
};

float4 PS(PixelInput input) : SV_TARGET
{
    float4 test = map.Sample(samp, input.uv);

    if (input.uv.y <= hpRate)
    {
        test.a = 0.0f;
    }

    return test;
}