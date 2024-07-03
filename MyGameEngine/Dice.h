#pragma once
#include"Quad.h"
#include"Transform.h"
class Dice : public Quad
{
public:
	Dice() :Quad() {};
	~Dice() override;
private:
	void InitVertexData() override; //’¸“_î•ñ‚Ì€”õ
    void InitIndexData() override;
	//-------------Draw‚©‚çŒÄ‚Î‚ê‚éŠÖ”-------------//
};

