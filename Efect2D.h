/*=======================================================================================================
概　略：エフェクトを扱う処理
作成日：10月26日
更新日：
制作者：Yu Nishimukai
=======================================================================================================*/
#pragma once

//---------------インクルード-----------------------
#include "Sprite.h"
#include <List>

class Efect2D
{
	Sprite *spt;
	D3DXVECTOR2 size;	//サイズ用の変数
	float Aspeed;		//アニメーション速度用の変数

	struct EffectData
	{
		float anime;		//アニメーション用の変数
		D3DXVECTOR3 position;	//描画位置の変数
	};

	std::list<EffectData> dataList;

public:
	Efect2D();
	~Efect2D();
	HRESULT Load(char* fileName, D3DXVECTOR2 s, float sp);
	void Draw();
	void Add(D3DXVECTOR3 pos);
};

