/*===========================================================================================
概　略：チュートリアルクラスヘッダー作成
作成日：01月22日
更新日：
制作者：Yu Nishimukai
=============================================================================================*/
#pragma once

//---------------インクルード-----------------------
#include "UnitBase.h" 
#include "Sprite.h"
#include "Audio.h"

class Tutorial : public UnitBase
{
	//オーディオクラスのオブジェクト作成
	Audio* audio;

	//スプライトクラスのオブジェクト作成
	Sprite sprite;


public:
	Tutorial();		//コンストラクタ
	~Tutorial();		//デストラクタ

	//画像読み込み
	HRESULT Load();

	//描画処理
	HRESULT Render();

	//更新処理
	HRESULT Update();
};


