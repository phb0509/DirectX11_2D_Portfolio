#include "Framework.h"

ConstBuffer::ConstBuffer(void* data, UINT dataSize)
	: data(data), dataSize(dataSize)
{
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	//D3D11_USAGE_DEFAULT = 0, //GPU���� �а� ���� ����
	//D3D11_USAGE_IMMUTABLE = 1,//GPU���� �б⸸ ����(���� �Ұ�)
	//D3D11_USAGE_DYNAMIC = 2,//CPU���� ���� ����, GPU�б�(Map, Unmap ��밡��)
	//D3D11_USAGE_STAGING = 3//GPU���� CPU�� �̵�(�б⸸ ����)
	bd.ByteWidth = dataSize;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	DEVICE->CreateBuffer(&bd, nullptr, &buffer);
}

ConstBuffer::~ConstBuffer()
{
	buffer->Release();
}

void ConstBuffer::Update()
{
	DC->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	memcpy(subResource.pData, data, dataSize);
	DC->Unmap(buffer, 0);
}

void ConstBuffer::SetVSBuffer(UINT slot)
{
	DC->VSSetConstantBuffers(slot, 1, &buffer);
	Update();
}

void ConstBuffer::SetPSBuffer(UINT slot)
{
	DC->PSSetConstantBuffers(slot, 1, &buffer);
	Update();
}

void ConstBuffer::SetGSBuffer(UINT slot)
{
	DC->GSSetConstantBuffers(slot, 1, &buffer);
	Update();
}

void ConstBuffer::SetCSBuffer(UINT slot)
{
	DC->CSSetConstantBuffers(slot, 1, &buffer);
	Update();
}
