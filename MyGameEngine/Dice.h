#pragma once
#include"Quad.h"
#include"Transform.h"
class Dice : public Quad
{
public:
	Dice() :Quad() {};
	~Dice() override;
private:
	void InitVertexData() override; //���_���̏���
    void InitIndexData() override;
	//-------------Draw����Ă΂��֐�-------------//
};

