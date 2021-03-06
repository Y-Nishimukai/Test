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

#define RESURRECTION 5	//復活する時間

class Tutorial : public UnitBase
{
	//オーディオクラスのオブジェクト作成
	Audio* audio;

	//スプライトクラスのオブジェクト作成
	Sprite sprite;

	Sprite sprite1;

	Sprite sprite2;

	Sprite spriteA;

	Sprite spriteB;

	//プレイヤーの状態を定数化
	enum
	{
		STATUS_NOMAL,		//通常
		STATUS_ATTACK,		//攻撃
	};
	int status;				//現在の状態

	int attackCount;			//攻撃してからの時間をカウント

	BOOL isCutKeyFlg;		//攻撃ボタン押したか
	int CutCnt;

	HRESULT Cut();			//攻撃処理
	HRESULT Attack();		//攻撃状態処理


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


