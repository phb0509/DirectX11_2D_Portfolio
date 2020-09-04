#pragma once

class Shader
{	
protected:
	wstring file;
	ID3DBlob* blob;
		
public:
	Shader();
	virtual ~Shader();

	virtual void Set() = 0;
};