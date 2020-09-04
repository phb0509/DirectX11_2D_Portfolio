#include "Framework.h"

StructuredBuffer::StructuredBuffer(void* inputData, UINT inputStride, UINT inputCount, UINT outputStride, UINT outputCount)
	: inputData(inputData), inputStride(inputStride), inputCount(inputCount),
	outputStride(outputStride), outputCount(outputCount)
{
	CreateInput();
	CreateSRV();
	CreateOutput();
	CreateUAV();
	CreateResult();
}

StructuredBuffer::~StructuredBuffer()
{
	input->Release();
	srv->Release();
	output->Release();
	uav->Release();
	result->Release();
}

void StructuredBuffer::Copy(void* data, UINT size)
{
	DC->CopyResource(result, output);

	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(result, 0, D3D11_MAP_READ, 0, &subResource);
	memcpy(data, subResource.pData, size);
	DC->Unmap(result, 0);
}

void StructuredBuffer::CreateInput()
{
	ID3D11Buffer* buffer;

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = inputStride * inputCount;
	bd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	bd.StructureByteStride = inputStride;

	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = inputData;

	DEVICE->CreateBuffer(&bd, &subResource, &buffer);

	input = (ID3D11Resource*)buffer;
}

void StructuredBuffer::CreateSRV()
{
	ID3D11Buffer* buffer = (ID3D11Buffer*)input;

	D3D11_BUFFER_DESC bd;
	buffer->GetDesc(&bd);

	D3D11_SHADER_RESOURCE_VIEW_DESC sd = {};
	sd.Format = DXGI_FORMAT_UNKNOWN;
	sd.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;	
	sd.BufferEx.FirstElement = 0;
	sd.BufferEx.NumElements = inputCount;

	DEVICE->CreateShaderResourceView(buffer, &sd, &srv);
}

void StructuredBuffer::CreateOutput()
{
	ID3D11Buffer* buffer;

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = outputStride * outputCount;
	bd.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
	bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	bd.StructureByteStride = outputStride;

	DEVICE->CreateBuffer(&bd, nullptr, &buffer);

	output = (ID3D11Resource*)buffer;
}

void StructuredBuffer::CreateUAV()
{
	ID3D11Buffer* buffer = (ID3D11Buffer*)output;

	D3D11_BUFFER_DESC bd;
	buffer->GetDesc(&bd);

	D3D11_UNORDERED_ACCESS_VIEW_DESC ud = {};
	ud.Format = DXGI_FORMAT_UNKNOWN;
	ud.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	ud.Buffer.FirstElement = 0;	
	ud.Buffer.NumElements = outputCount;

	DEVICE->CreateUnorderedAccessView(buffer, &ud, &uav);
}

void StructuredBuffer::CreateResult()
{
	ID3D11Buffer* buffer;

	D3D11_BUFFER_DESC bd = {};
	((ID3D11Buffer*)output)->GetDesc(&bd);
	bd.Usage = D3D11_USAGE_STAGING;
	bd.BindFlags = 0;
	bd.MiscFlags = 0;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	DEVICE->CreateBuffer(&bd, nullptr, &buffer);

	result = (ID3D11Resource*)buffer;
}
