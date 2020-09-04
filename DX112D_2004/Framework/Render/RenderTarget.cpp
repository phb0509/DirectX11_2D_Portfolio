#include "Framework.h"

RenderTarget::RenderTarget(UINT width, UINT height)
	: width(width), height(height)
{
	{//Create RTV Texture
		D3D11_TEXTURE2D_DESC desc = {};
		desc.Width = width;
		desc.Height = height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;

		DEVICE->CreateTexture2D(&desc, nullptr, &rtvTexture);
	}

	{//Create RTV
		D3D11_RENDER_TARGET_VIEW_DESC desc = {};
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

		DEVICE->CreateRenderTargetView(rtvTexture, &desc, &rtv);
	}

	{//Create SRV
		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = 1;

		DEVICE->CreateShaderResourceView(rtvTexture, &desc, &srv);
	}
}

RenderTarget::~RenderTarget()
{
	rtvTexture->Release();

	srv->Release();
	rtv->Release();
}

void RenderTarget::Set()
{
	Camera::Get()->SetViewport(width, height);
	Camera::Get()->SetOrthographic(width, height);

	DC->OMSetRenderTargets(1, &rtv, nullptr);

	float clearColor[4] = { 1, 1, 1, 1 };
	DC->ClearRenderTargetView(rtv, clearColor);		
}
