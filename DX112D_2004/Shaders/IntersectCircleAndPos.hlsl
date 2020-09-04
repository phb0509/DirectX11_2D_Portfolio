//IntersectCircleAndPos
struct InputDesc
{
    float2 pos;
    float radius;
    uint index;
};
StructuredBuffer<InputDesc> input;

struct OutputDesc
{
    uint collisionIndex;
};
RWStructuredBuffer<OutputDesc> output;

cbuffer MousePos : register(b0)
{
    float2 mousePos;
    float size;
}

void Intersect(uint index)
{
    float dist = distance(input[index].pos, mousePos);
    
    [branch]
    if(dist < input[index].radius)
        output[0].collisionIndex = input[index].index;
}

[numthreads(16, 16, 1)]
void CS( uint3 groupID : SV_GroupID, uint groupIndex : SV_GroupIndex )
{
    uint index = groupID.x * 16 * 16 + groupIndex;
    
    if(size > index)
        Intersect(index);
}