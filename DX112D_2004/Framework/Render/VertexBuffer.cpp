#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(void* data, UINT stride, UINT count)
    : stride(stride)
{
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = stride * count;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = data;

    DEVICE->CreateBuffer(&bd, &initData, &buffer);
}

VertexBuffer::~VertexBuffer()
{
    buffer->Release();
}

void VertexBuffer::Set(UINT slot)
{
    DC->IASetVertexBuffers(slot, 1, &buffer, &stride, &offset);
}

void VertexBuffer::Update(void* data, UINT count)
{
    DC->UpdateSubresource(buffer, 0, nullptr, data, stride, count);
}
