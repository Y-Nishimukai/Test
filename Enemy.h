/*===========================================================================================
概　略：エネミー処理のヘッダー作成
作成日：10月26日
更新日：
制作者：Yu Nishimukai
=============================================================================================*/
#pragma once

//---------------インクルード-----------------------
#include "UnitBase.h"
#include "Sprite.h"
#include "Audio.h"
#include "Efect2D.h"

//ユニットベースクラスを継承
class Enemy : public UnitBase
{
	//オーディオクラスのオブジェクト作成
	Audio* audio;

	//スプライトクラスのオブジェクト作成
	Sprite sprite;

	//エフェクトクラスのオブジェクト作成
	Efect2D* efect;

	POINT move;			//移動速度
	int action;
	int DeathCount;
	int zannzou;

	HRESULT Move();		//移動

	BOOL  isLive;		//生きているフラグ（FALSEになると死亡）

public:
	Enemy();		//コンストラクタ
	~Enemy();		//デストラクタ

	HRESULT Load();		//読み込み処理
	HRESULT Hit(UnitBase* pTarget);
	HRESULT Update();	//更新処理
	HRESULT Render();	//描画処理

	void Kill();		//敵が死亡したとき

	BOOL GetLive(){ return isLive; }
};

