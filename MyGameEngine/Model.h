#pragma once
#include<string>
#include"Engine/FBX.h"
namespace Model
{
	struct ModelData
	{
		FBX* pFbx_;
		Transform transform_;
		std::string filename_;
		ModelData() :pFbx_(nullptr), filename_("") {}
	};
	//モデルの一覧を保存する配列(vector or list)
	int Load(std::string filename);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);
	void Release();
};

