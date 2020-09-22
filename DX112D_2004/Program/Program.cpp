#include "Framework.h"

#include "Scenes/MirkWoodScene.h"
#include "Scenes/ElvenGardenScene.h"



Program::Program()
{	
	//scene = new MirkWoodScene();
	SCENE->Add("ElvenGarden", new ElvenGardenScene());
	SCENE->Add("Mirkwood", new MirkWoodScene());

	SCENE->ChangeScene("ElvenGarden");
}

Program::~Program()
{
	delete scene;	
}

void Program::Update()
{
	Keyboard::Get()->Update();
	Timer::Get()->Update();	

	SCENE->Update();

	Camera::Get()->Update();

	EffectManager::Get()->Update();
	UIManager::Get()->Update();

	mouseWheel = 0;
}

void Program::Render()
{		
	ALPHA_BLEND_STATE->SetState();
	SCENE->PreRender();
		
	Device::Get()->SetRenderTarget();
	Device::Get()->Clear();	

	Camera::Get()->SetViewport();
	Camera::Get()->SetOrthographic();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();	

	//ImGui::Text("FPS : %d", Timer::Get()->GetFPS());	

	ALPHA_BLEND_STATE->SetState();
	SCENE->Render();

	DirectWrite::Get()->GetDC()->BeginDraw();

	wstring fps = L"FPS : " + to_wstring((int)Timer::Get()->GetFPS());
	wstring time = L"Time : " + to_wstring((int)Timer::Get()->GetRunTime());
	RECT fpsRect = { 0, 0, 100, 100 };
	RECT timeRect = { 0, 25, 100, 100 };

	DirectWrite::Get()->RenderText(fps, fpsRect);
	DirectWrite::Get()->RenderText(time, timeRect);

	EffectManager::Get()->Render();

	Camera::Get()->PostRender();
	SCENE->PostRender();
	UIManager::Get()->Render();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	DirectWrite::Get()->GetDC()->EndDraw();

	Device::Get()->Present();
}
