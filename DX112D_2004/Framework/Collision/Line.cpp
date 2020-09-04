#include "Framework.h"
#include "Line.h"

Line::Line(Vector2 start, Vector2 end)
    : start(start), end(end)
{
}

Line::~Line()
{
}

bool Line::IsBetween(Line line)
{
    Vector2 A = line.start - start;
    Vector2 B = line.end - start;

    float crossA = A.Cross(end - start);
    float crossB = B.Cross(end - start);

    return crossA * crossB < 0;
}

bool Line::IsCollision(Line line)
{
    return IsBetween(line) && line.IsBetween(*this);
}
