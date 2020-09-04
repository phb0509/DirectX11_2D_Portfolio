#include "Framework.h"
#include "WVPScene.h"

WVPScene::WVPScene()
	: pos(0, 0), pos2(0, 0), camPos(0, 0), angle(0), size(1, 1), pivot(0, 0)
{
	texture = new Texture(L"Textures/sample.png");

	worldBuffer = new MatrixBuffer();
	viewBuffer = new MatrixBuffer();
	projectionBuffer = new MatrixBuffer();

	worldBuffer2 = new MatrixBuffer();

	Matrix projection = XMMatrixOrthographicLH(
		(float)WIN_WIDTH, (float)WIN_HEIGHT, -1.0f, 1.0f);
	projectionBuffer->Set(projection);
	projectionBuffer->Update();

	world2 = XMMatrixTranslation(200, 200, 0);	
}

WVPScene::~WVPScene()
{
	delete texture;

	delete worldBuffer;
	delete viewBuffer;
	delete projectionBuffer;
}

void WVPScene::Update()
{
	if (KEY_PRESS(VK_RIGHT))
	{
		pos.x += 100 * DELTA;
	}
	if (KEY_PRESS(VK_LEFT))
	{
		pos.x -= 100 * DELTA;
	}
	if (KEY_PRESS(VK_UP))
	{
		pos.y += 100 * DELTA;
	}
	if (KEY_PRESS(VK_DOWN))
	{
		pos.y -= 100 * DELTA;
	}	

	XMMATRIX T = XMMatrixTranslation(pos.x, pos.y, 0);

	if (KEY_PRESS('L'))
	{
		size.x += DELTA;
	}
	if (KEY_PRESS('J'))
	{
		size.x -= DELTA;
	}
	if (KEY_PRESS('I'))
	{		
		size.y += DELTA;
	}
	if (KEY_PRESS('K'))
	{
		size.y -= DELTA;
	}

	Matrix S = XMMatrixScaling(size.x, size.y, 1);

	if (KEY_PRESS(VK_ADD))
		angle += DELTA;
	if (KEY_PRESS(VK_SUBTRACT))
		angle -= DELTA;

	Matrix R = XMMatrixRotationZ(angle);

	Matrix P, IP;
	P = XMMatrixTranslation(pivot.x, pivot.y, 0);
	IP = XMMatrixInverse(nullptr, P);

	Matrix world = IP * S * R * T * P;
	worldBuffer->Set(IP * S * R * T * P);	

	worldBuffer2->Set(world2 * world);

	if (KEY_PRESS('W'))
	{
		camPos.y += 100 * DELTA;
	}
	if (KEY_PRESS('S'))
	{
		camPos.y -= 100 * DELTA;
	}
	if (KEY_PRESS('A'))
	{
		camPos.x -= 100 * DELTA;
	}
	if (KEY_PRESS('D'))
	{
		camPos.x += 100 * DELTA;
	}

	XMMATRIX view = XMMatrixTranslation(camPos.x, camPos.y, 0);
	viewBuffer->Set(view);

	texture->Update();
	worldBuffer->Update();
	worldBuffer2->Update();
	viewBuffer->Update();
}

void WVPScene::Render()
{
	worldBuffer->SetVSBuffer(0);
	viewBuffer->SetVSBuffer(1);
	projectionBuffer->SetVSBuffer(2);

	texture->Render();

	worldBuffer2->SetVSBuffer(0);

	texture->Render();
}
