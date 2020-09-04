#include "Framework.h"

int Math::Random(const int& min, const int& max)
{
    return rand() % (max - min) + min;
}

float Math::Random(const float& min, const float& max)
{
    float normal = rand() / (float)RAND_MAX;

    return normal * (max - min) + min;
}
