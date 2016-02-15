/*===========================================================================================
概　略：クリアクラスヘッダー作成
作成日：10月26日
更新日：
制作者：Yu Nishimukai
=============================================================================================*/
#pragma once

//---------------インクルード-----------------------
#include "UnitBase.h"
#include "Sprite.h"

class Clear : public UnitBase
{
	//スプライトクラスのオブジェクト作成
	Sprite sprite;
	Sprite spriteG;
	Sprite spriteM;

public:
	Clear();	//コンストラクタ
	~Clear();	//デストラクタ

	HRESULT Load();		//読み込み処理
	HRESULT Update();	//更新処理
	HRESULT Render();	//描画処理
};
