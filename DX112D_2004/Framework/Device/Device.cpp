#include "Framework.h"

Device* Device::instance = nullptr;

Device::Device(HWND hWnd)
	: hWnd(hWnd)
{    
	CreateDeviceAndSwapChain();
	CreateBackBuffer();        
}

Device::~Device()
{
	device->Release();
	deviceContext->Release();
	swapChain->Release();
	renderTargetView->Release();
}

void Device::CreateDeviceAndSwapChain()
{
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT featureSize = ARRAYSIZE(featureLevels);

    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;
    sd.BufferDesc.Width = WIN_WIDTH;
    sd.BufferDesc.Height = WIN_HEIGHT;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;    
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = true;

    D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT,
        featureLevels,
        featureSize,
        D3D11_SDK_VERSION,
        &sd,
        &swapChain,
        &device,
        nullptr,
        &deviceContext
    );
}

void Device::CreateBackBuffer()
{
    ID3D11Texture2D* backBuffer;

    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
    backBuffer->Release();

    deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);   
}

void Device::SetRenderTarget()
{
    deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
}

void Device::Clear()
{
    float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    deviceContext->ClearRenderTargetView(renderTargetView, clearColor);
}

void Device::Present()
{
    swapChain->Present(0, 0);
}
