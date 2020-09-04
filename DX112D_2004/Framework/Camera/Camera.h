#pragma once

class Camera : public Transform
{
private:
	float speed;
	float zoomSpeed;

	Transform* target;
	Vector2 offset;

	Vector2 leftBottom;
	Vector2 rightTop;

	float duration;
	float reduceDamping;
	float magnitude;

	Vector2 originPos;

	MatrixBuffer* projectionBuffer;

	static Camera* instance;

	Camera();
	~Camera();
public:
	static Camera* Get() { return instance; }
	static void Create() { instance = new Camera(); }
	static void Delete() { delete instance; }

	void Update();
	void PostRender();

	void ShakeStart(float magnitude, float duration, float reduceDamping = 0.0f);

	void SetViewport(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
	void SetOrthographic(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);

	void SetTarget(Transform* value) { target = value; }
	void SetLeftBottom(Vector2 value) { leftBottom = value; }
	void SetRightTop(Vector2 value) { rightTop = value; }

	Vector2 GetMouseWorldPos();

private:
	void FreeMode();
	void FollowMode();
	void Shake();
};