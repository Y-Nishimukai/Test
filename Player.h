/*===========================================================================================
概　略：プレイヤー処理のヘッダー作成
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

//定数定義
#define MOVE_SPEED 7	//移動速度
#define SHOT_LIMIT 1	//弾の撃てる上限
#define RESURRECTION 5	//復活する時間

//ユニットベースクラスの継承
class Player : public UnitBase
{
	//オーディオクラスのオブジェクト作成
	Audio* audio;

	//スプライトクラスのオブジェクト作成
	Sprite sprite;

	Sprite spriteA;

	Sprite spriteNum;

	//エフェクトクラスのオブジェクト作成
	Efect2D* efect;

	BOOL bgm_flg;		//BGMを鳴らしたかのフラグ
	BOOL stick_flg;		//スティックを倒したかのフラグ

	int anime1;
	int anime10;
	int anime100;

	//プレイヤーの状態を定数化
	enum
	{
		STATUS_NOMAL,		//通常
		STATUS_ATTACK,		//攻撃
	};
	int status;				//現在の状態


	int attackCount;			//攻撃してからの時間をカウント

	BOOL isCutKeyFlg;		//攻撃ボタン押したか
	int killCount;			//敵を何体倒したか数える
	int CutCnt;

	//private関数
	HRESULT Cut();			//攻撃処理
	HRESULT Attack();		//攻撃状態処理
	void Bgm();				//BGMを鳴らす

public:
	Player();		//コンストラクタ
	~Player();		//デストラクタ

	HRESULT Load();						//読み込み処理
	HRESULT Update();					//更新処理
	HRESULT Render();					//描画処理
	HRESULT Hit(UnitBase* pTarget);		//衝突処理

	D3DXVECTOR3 GetPlayer(){ return position; }
};

