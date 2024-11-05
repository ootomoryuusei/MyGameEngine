#pragma once

#include<vector>
#include<string>
#include"Engine/Sprite.h"
#include"Engine/Transform.h"
namespace Image
{
	struct ImageData {
		std::string fileName;
		Sprite* pSprite;
		RECT rect;
		Transform transform;
		ImageData() : pSprite(nullptr) {
			fileName = "";
			pSprite = nullptr;
		}
	};

	void Initialize();
	int Load(std::string fileName);
	void Draw(int handle);
	void Release(int handle);
	void AllRelease();

	void ResetRect(int handle);

	void SetRect(int handle, int x, int y, int width, int height);

	void SetTransform(int handle, Transform& transform);

	XMMATRIX GetMatrix(int handle);
};

