#include "Framework.h"
#include "RenderTargetScene.h"

RenderTargetScene::RenderTargetScene()
{
	renderTarget = new RenderTarget();

	bg = new Quad(L"Textures/sample.png", L"TextureShader");
	bg->pos = { CENTER_X, CENTER_Y };
	plane = new Quad(L"Textures/sun.png", L"TextureShader");
	plane->pos = { CENTER_X, CENTER_Y };

	Texture* renderTexture = Texture::Add(L"Target", renderTarget->GetSRV());

	targetTexture = new Quad(L"GrayscaleShader");	
	targetTexture->SetTexture(renderTexture);
	targetTexture->scale = { WIN_WIDTH / 2, WIN_HEIGHT  / 2};
	targetTexture->pos = { CENTER_X - WIN_WIDTH /4, CENTER_Y - WIN_HEIGHT/4};

	targetTexture2 = new Quad(L"FilterShader");	
	targetTexture2->SetTexture(renderTexture);
	targetTexture2->scale = { WIN_WIDTH / 2, WIN_HEIGHT / 2 };
	targetTexture2->pos = { CENTER_X + WIN_WIDTH / 4, CENTER_Y - WIN_HEIGHT / 4 };

	knight = new Knight();

	viewBuffer = new MatrixBuffer();

	intBuffer = new IntBuffer();
	floatBuffer = new FloatBuffer();
	colorBuffer = new ColorBuffer();

	floatBuffer->data.value[0] = WIN_WIDTH;
	floatBuffer->data.value[1] = WIN_HEIGHT;
}

RenderTargetScene::~RenderTargetScene()
{
	delete renderTarget;
	delete bg;
	delete plane;
	delete knight;
	delete viewBuffer;
	delete intBuffer;
	delete floatBuffer;
	delete colorBuffer;

	delete targetTexture;
	delete targetTexture2;
}

void RenderTargetScene::Update()
{
	targetTexture->Update();
	targetTexture2->Update();

	bg->Update();
	plane->Update();
	knight->Update();

	floatBuffer->data.value[2] = knight->pos.x;
	floatBuffer->data.value[3] = WIN_HEIGHT - knight->pos.y;
}

void RenderTargetScene::PreRender()
{	
	renderTarget->Set();

	BLEND_STATE->SetState();	

	bg->Render();
	plane->Render();
	knight->Render();
}

void RenderTargetScene::Render()
{
	viewBuffer->SetVSBuffer(1);
	intBuffer->SetPSBuffer(1);
	floatBuffer->SetPSBuffer(2);
	colorBuffer->SetPSBuffer(0);
	targetTexture->Render();	
	targetTexture2->Render();
}

void RenderTargetScene::PostRender()
{
	ImGui::SliderInt("Range", &intBuffer->data.index[0], 0, 2);
	ImGui::SliderInt("Value", &intBuffer->data.index[1], 0, 100);
}
