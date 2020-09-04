#include "Framework.h"
#include "ComputeScene.h"

ComputeScene::ComputeScene()
{
	UINT width = 50;
	UINT height = 50;

	size = width * height;

	input = new InputDesc[size];
	output = new OutputDesc();

	for (UINT y = 0; y < height; y++)
	{
		for (UINT x = 0; x < width; x++)
		{
			float radius = 10.0f;
			CircleCollider* collider = new CircleCollider(radius);
			collider->pos = { radius * x * 2 , radius * y * 2 };

			int index = y * width + x;
			input[index].pos = collider->pos;
			input[index].radius = radius;
			input[index].index = index;

			colliders.push_back(collider);
		}
	}

	CreateCompute();
}

ComputeScene::~ComputeScene()
{
	for (Collider* col : colliders)
		delete col;
}

void ComputeScene::Update()
{
	mouseBuffer->data.value[0] = mousePos.x;
	mouseBuffer->data.value[1] = mousePos.y;

	computeShader->Set();

	mouseBuffer->SetCSBuffer(0);

	DC->CSSetShaderResources(0, 1, &structuredBuffer->GetSRV());
	DC->CSSetUnorderedAccessViews(0, 1, &structuredBuffer->GetUAV(), nullptr);

	UINT x = ceil((float)size / 256.0f);
	DC->Dispatch(x, 1, 1);

	structuredBuffer->Copy(output, sizeof(OutputDesc));

	colliders[output[0].inCircle]->SetColor(Float4(1, 0, 0, 1));

	for (Collider* col : colliders)
		col->Update();
}

void ComputeScene::Render()
{
	for (Collider* col : colliders)
		col->Render();
}

void ComputeScene::PostRender()
{
}

void ComputeScene::Raw()
{
	ComputeShader* shader = SHADER->AddCS(L"ByteAddress");

	struct Output
	{
		UINT groupID[3];
		UINT groupThreadID[3];
		UINT dispatchThreadID[3];
		UINT groupIndex;
	};

	UINT size = 10 * 8 * 3 * 4;

	Output* output = new Output[size];
	RawBuffer* buffer = new RawBuffer(sizeof(Output) * size);

	ID3D11UnorderedAccessView* uav = buffer->GetUAV();
	DC->CSSetUnorderedAccessViews(0, 1, &uav, nullptr);

	shader->Set();

	DC->Dispatch(4, 1, 1);

	buffer->Copy(output, sizeof(Output)* size);

	FILE* file;
	fopen_s(&file, "TextData/RawData.csv", "w");

	for (UINT i = 0; i < size; i++)
	{
		Output temp = output[i];

		fprintf(
			file,
			"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
			i,
			temp.groupID[0], temp.groupID[1], temp.groupID[2],
			temp.groupThreadID[0], temp.groupThreadID[1], temp.groupThreadID[2],
			temp.dispatchThreadID[0], temp.dispatchThreadID[1], temp.dispatchThreadID[2],
			temp.groupIndex
		);		
	}

	fclose(file);
}

void ComputeScene::CreateCompute()
{
	computeShader = SHADER->AddCS(L"IntersectCircleAndPos");

	structuredBuffer = new StructuredBuffer(input,
		sizeof(InputDesc), size, sizeof(OutputDesc), 1);

	mouseBuffer = new FloatBuffer();
	mouseBuffer->data.value[2] = (float)size;
}
