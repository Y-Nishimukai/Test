/*===========================================================================================
概　略：タイトルクラスヘッダー作成
作成日：10月26日
更新日：
制作者：Yu Nishimukai
=============================================================================================*/
#pragma once

//---------------インクルード-----------------------
#include "UnitBase.h" 
#include "Sprite.h"
#include "Audio.h"

#define TIMELAG 60

class Title : public UnitBase
{
	//オーディオクラスのオブジェクト作成
	Audio* audio;

	//スプライトクラスのオブジェクト作成
	Sprite sprite1;

	Sprite sprite2;

	//プレイヤーの状態を定数化
	enum
	{
		STATUS_NOMAL,		//通常
		STATUS_CUT,		//攻撃
	};
	int status;				//現在の状態
	
	int lag;
	bool isSpace;

	HRESULT Cut();

public:
	Title();		//コンストラクタ
	~Title();		//デストラクタ

	//画像読み込み
	HRESULT Load();

	//描画処理
	HRESULT Render();

	//更新処理
	HRESULT Update();
};


