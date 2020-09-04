#include "Framework.h"

ConstBuffer::ConstBuffer(void* data, UINT dataSize)
	: data(data), dataSize(dataSize)
{
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	//D3D11_USAGE_DEFAULT = 0, //GPU에서 읽고 쓰기 가능
	//D3D11_USAGE_IMMUTABLE = 1,//GPU에서 읽기만 가능(수정 불가)
	//D3D11_USAGE_DYNAMIC = 2,//CPU에서 쓰기 가능, GPU읽기(Map, Unmap 사용가능)
	//D3D11_USAGE_STAGING = 3//GPU에서 CPU로 이동(읽기만 가능)
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
