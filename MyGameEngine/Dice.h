#pragma once
#include"Quad.h"
#include"Transform.h"
class Dice : public Quad
{
public:
	Dice() :Quad() {};
	~Dice() override;
private:
	void InitVertexData() override; //頂点情報の準備
    void InitIndexData() override;
	//-------------Drawから呼ばれる関数-------------//
};

