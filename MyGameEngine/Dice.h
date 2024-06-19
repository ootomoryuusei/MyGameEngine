#pragma once
#include"Quad.h"
class Dice : public Quad
{
private:
public:
	Dice();
	~Dice();
	virtual HRESULT Initialize();
	virtual void Draw(XMMATRIX& worldMatrix);
	void Release();
};

