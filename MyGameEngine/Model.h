#pragma once
#include<string>
namespace Model
{
	struct ModelData
	{
		//FBX
		//Transform
		//FileName
	};
	//モデルの一覧を保存する配列(vector or list)
	int Load(std::string filename);
};

int Model::Load(std::string filename) {
	//ファイル名のモデルを読み込む
	//同じモデルがすでに読み込まえていたら、エラー、－１を返す
	//初めての読み込みだったら、モデルを読み込んで、配列に追加
	return 0;
}

