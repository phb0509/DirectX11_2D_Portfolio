#include "Framework.h"
#include "PixelShaderScene.h"

PixelShaderScene::PixelShaderScene()
{
	quad = new Quad(L"Textures/sample.png", L"LightShader");
	quad->pos = { CENTER_X, CENTER_Y };

	colorBuffer = new ColorBuffer();
	intBuffer = new IntBuffer();
	floatBuffer = new FloatBuffer();

	floatBuffer->data.value[0] = quad->GetSize().x;
	floatBuffer->data.value[1] = quad->GetSize().y;

	texture = Texture::Add(L"Textures/sun.png");
}

PixelShaderScene::~PixelShaderScene()
{
	delete quad;
	delete colorBuffer;
	delete intBuffer;
	delete floatBuffer;
}

void PixelShaderScene::Update()
{
	floatBuffer->data.value[2] = mousePos.x;
	floatBuffer->data.value[3] = mousePos.y;

	quad->Update();
}

void PixelShaderScene::Render()
{
	texture->Set(1);

	colorBuffer->SetPSBuffer(0);
	intBuffer->SetPSBuffer(1);
	floatBuffer->SetPSBuffer(2);
	quad->Render();
}

void PixelShaderScene::PostRender()
{
	ImGui::ColorEdit4("Color", (float*)&colorBuffer->data.color);
	ImGui::SliderInt("Range", &intBuffer->data.index[0], 0, 1000);
	//ImGui::SliderInt("Range", &intBuffer->data.index[1], 0, 10);
	//ImGui::SliderInt("Value1", &intBuffer->data.index[2], 0, 50);
	//ImGui::SliderInt("Value2", &intBuffer->data.index[3], 0, 50);
}
