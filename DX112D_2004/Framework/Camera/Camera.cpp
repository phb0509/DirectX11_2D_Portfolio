#include "Framework.h"

Camera* Camera::instance = nullptr;

Camera::Camera()
	: speed(200), offset(CENTER_X, CENTER_Y), 
	duration(0), reduceDamping(0), magnitude(0), zoomSpeed(1)
{
	SetWorldBuffer(1);
	projectionBuffer = new MatrixBuffer();
}

Camera::~Camera()
{
}

void Camera::Update()
{
	if (target == nullptr)
		FreeMode();
	else
		FollowMode();

	Shake();

	UpdateWorld();
	SetWorldBuffer(1);
	worldBuffer->SetGSBuffer(1);
}

void Camera::PostRender()
{
	ImGui::Text("CameraOption");
	ImGui::Text("CamX : %.1f, CamY : %.1f", pos.x, pos.y);
	ImGui::SliderFloat("CamSpeed", &speed, 0, 500);
	ImGui::SliderFloat2("CamOffset", (float*)&offset, 0, 1000);

	ImGui::Text("Gunner Position");
	ImGui::Text("X : %.1f, Y : %.1f", GM->GetGunner()->pos.x, GM->GetGunner()->pos.y);
}

Vector2 Camera::GetMouseWorldPos()
{
	Matrix invView = XMMatrixInverse(nullptr, matrix);

	return Vector2::TransformCoord(mousePos, invView);
}

void Camera::FreeMode()
{
	if (KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_PRESS('W'))
		{
			pos.y -= speed * DELTA;
		}
		if (KEY_PRESS('S'))
		{
			pos.y += speed * DELTA;
		}
		if (KEY_PRESS('A'))
		{
			pos.x += speed * DELTA;
		}
		if (KEY_PRESS('D'))
		{
			pos.x -= speed * DELTA;
		}
	}

	if (mouseWheel != 0)
	{
		scale += mouseWheel * zoomSpeed * DELTA;

		if (scale.x < 0.1f || scale.y < 0.1f)
			scale = Vector2(0.1f, 0.1f);
	}
}

void Camera::FollowMode()
{
	Vector2 targetPos = target->pos - offset;

	if (targetPos.x < leftBottom.x)
		targetPos.x = leftBottom.x;

	if (targetPos.x > rightTop.x - WIN_WIDTH)
		targetPos.x = rightTop.x - WIN_WIDTH;

	if (targetPos.y < leftBottom.y)
		targetPos.y = leftBottom.y;

	if (targetPos.y > rightTop.y - WIN_HEIGHT)
		targetPos.y = rightTop.y - WIN_HEIGHT;

		
	pos = LERP(pos, targetPos * -1, DELTA * speed);
}

void Camera::ShakeStart(float magnitude, float duration, float reduceDamping)
{
	this->magnitude = magnitude;
	this->duration = duration;
	this->reduceDamping = reduceDamping;

	originPos = pos;
}

void Camera::SetViewport(UINT width, UINT height)
{
	D3D11_VIEWPORT vp;
	vp.Width = (float)width;
	vp.Height = (float)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	DC->RSSetViewports(1, &vp);
}

void Camera::SetOrthographic(UINT width, UINT height)
{
	Matrix orthographic = XMMatrixOrthographicOffCenterLH(0, width,
		0, height, -1.0f, 1.0f);

	projectionBuffer->Set(orthographic);
	projectionBuffer->SetVSBuffer(2);
	projectionBuffer->SetGSBuffer(2);
}

void Camera::Shake()
{
	if (duration <= 0.0f)
		return;

	duration -= DELTA;
	magnitude -= DELTA * reduceDamping;
	if (magnitude < 0.0f)
	{
		magnitude = 0.0f;
		duration = 0.0f;
	}

	Vector2 temp;
	temp.x = Math::Random(-magnitude, magnitude);
	temp.y = Math::Random(-magnitude, magnitude);
	pos = originPos + temp;

	if (duration <= 0.0f)
		pos = originPos;
}
