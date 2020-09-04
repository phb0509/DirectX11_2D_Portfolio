#pragma once

class ConstBuffer
{
private:
	ID3D11Buffer* buffer;

	void* data;
	UINT dataSize;

	D3D11_MAPPED_SUBRESOURCE subResource;
public:
	ConstBuffer(void* data, UINT dataSize);
	virtual ~ConstBuffer();
	
	void SetVSBuffer(UINT slot);
	void SetPSBuffer(UINT slot);
	void SetGSBuffer(UINT slot);
	void SetCSBuffer(UINT slot);

private:
	void Update();
};
