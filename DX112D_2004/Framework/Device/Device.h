#pragma once



class Device
{
private:
	HWND hWnd;

	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* renderTargetView;

	static Device* instance;

	Device(HWND hWnd);
	~Device();
public:
	static Device* Get() { return instance; }
	static void Create(HWND hWnd) { instance = new Device(hWnd); }
	static void Delete() { delete instance; }

	void CreateDeviceAndSwapChain();
	void CreateBackBuffer();

	void SetRenderTarget();

	void Clear();
	void Present();

	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDeviceContext() { return deviceContext; }
	IDXGISwapChain* GetSwapChain() { return swapChain; }
};

