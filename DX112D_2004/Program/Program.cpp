#include "Framework.h"

//#include "Scenes/TurorialScene.h"
//#include "Scenes/WVPScene.h"
//#include "Scenes/SolarSystemScene.h"
#include "Scenes/CollisionScene.h"
//#include "Scenes/OffsetTestScene.h"
#include "Scenes/UVTestScene.h"
#include "Scenes/EffectScene.h"
#include "Scenes/PixelShaderScene.h"
#include "Scenes/RenderTargetScene.h"
#include "Scenes/MapToolScene.h"
#include "Scenes/AStarScene.h"
#include "Scenes/FontScene.h"
#include "Scenes/GeometryScene.h"
#include "Scenes/ComputeScene.h"
#include "Scenes/InstanceScene.h"
#include "Scenes/TriangleCollisionScene.h"

Program::Program()
{	
	//scene = new TutorialScene();
	//scene = new WVPScene();
	//scene = new SolarSystemScene();
	//scene = new CollisionScene();
	//scene = new OffsetTestScene();
	scene = new UVTestScene();
	//scene = new EffectScene();
	//scene = new PixelShaderScene();
	//scene = new RenderTargetScene();
	//scene = new MapToolScene();
	//scene = new AStarScene();
	//scene = new FontScene();
	//scene = new GeometryScene();
	//scene = new ComputeScene();
	//scene = new InstanceScene();
	//scene = new TriangleCollisionScene();
}

Program::~Program()
{
	delete scene;	
}

void Program::Update()
{
	Keyboard::Get()->Update();
	Timer::Get()->Update();	

	scene->Update();

	Camera::Get()->Update();

	EffectManager::Get()->Update();

	mouseWheel = 0;
}

void Program::Render()
{		
	ALPHA_BLEND_STATE->SetState();
	scene->PreRender();
		
	Device::Get()->SetRenderTarget();
	Device::Get()->Clear();	

	Camera::Get()->SetViewport();
	Camera::Get()->SetOrthographic();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();	

	//ImGui::Text("FPS : %d", Timer::Get()->GetFPS());	

	ALPHA_BLEND_STATE->SetState();
	scene->Render();

	DirectWrite::Get()->GetDC()->BeginDraw();

	wstring fps = L"FPS : " + to_wstring((int)Timer::Get()->GetFPS());
	wstring time = L"Time : " + to_wstring((int)Timer::Get()->GetRunTime());
	RECT fpsRect = { 0, 0, 100, 100 };
	RECT timeRect = { 0, 25, 100, 100 };

	DirectWrite::Get()->RenderText(fps, fpsRect);
	DirectWrite::Get()->RenderText(time, timeRect);

	EffectManager::Get()->Render();

	Camera::Get()->PostRender();
	scene->PostRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	DirectWrite::Get()->GetDC()->EndDraw();

	Device::Get()->Present();
}
