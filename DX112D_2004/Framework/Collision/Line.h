#pragma once

class Line
{
private:
	Vector2 start;
	Vector2 end;

public:
	Line(Vector2 start, Vector2 end);
	~Line();

	bool IsBetween(Line line);
	bool IsCollision(Line line);

	Vector2 Start() { return start; }
	Vector2 End() { return end; }
};