#pragma once

class ComputeScene : public Scene
{
private:
	vector<Collider*> colliders;

	struct InputDesc
	{
		Float2 pos;
		float radius;
		UINT index;
	};

	struct OutputDesc
	{
		UINT inCircle;
	};

	ComputeShader* computeShader;
	FloatBuffer* mouseBuffer;
	StructuredBuffer* structuredBuffer;
	InputDesc* input;
	OutputDesc* output;

	UINT size;
public:
	ComputeScene();
	~ComputeScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void Raw();
	void CreateCompute();
};