/*===========================================================================================
概　略：待機クラスヘッダー作成
作成日：02月12日
更新日：
制作者：Yu Nishimukai
=============================================================================================*/
#pragma once

//---------------インクルード-----------------------
#include "UnitBase.h" 
#include "Sprite.h"
#include "Audio.h"

#define RESURRECTION 5
#define WAITING 180	//復活する時間

class Waiting : public UnitBase
{
	//オーディオクラスのオブジェクト作成
	Audio* audio;

	//スプライトクラスのオブジェクト作成
	Sprite sprite;

	Sprite sprite1;

	Sprite sprite2;

	Sprite spriteA;

	Sprite spriteB;

	Sprite spriteIti;

	Sprite spriteNi;

	Sprite spriteSan;

	//プレイヤーの状態を定数化
	enum
	{
		STATUS_NOMAL,		//通常
		STATUS_ATTACK,		//攻撃
	};
	int status;				//現在の状態

	int attackCount;			//攻撃してからの時間をカウント
	int waiting;

	BOOL isWait;
	BOOL isCutKeyFlg;		//攻撃ボタン押したか
	BOOL count3;
	BOOL count2;
	BOOL count1;
	int CutCnt;

	HRESULT Cut();			//攻撃処理
	HRESULT Attack();		//攻撃状態処理


public:
	Waiting();		//コンストラクタ
	~Waiting();		//デストラクタ

	//画像読み込み
	HRESULT Load();

	//描画処理
	HRESULT Render();

	//更新処理
	HRESULT Update();
};


