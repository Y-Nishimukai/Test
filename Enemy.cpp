/*===========================================================================================
概　略：エネミー処理の関数定義
作成日：10月26日
更新日：
制作者：Yu Nishimukai
=============================================================================================*/

//---------------インクルード-----------------------
#include "Enemy.h"
#include "Player.h"
#include "stdlib.h"
#include "time.h"

//――――――――――――――――――――――
//	コンストラクタ
//――――――――――――――――――――――
Enemy::Enemy()
{
	//初期位置
	position.x = 0;							//画面の１番左に表示
	position.y = rand() % WINDOW_HEIGHT;	//ランダムな縦位置に表示

	action = 0;
	DeathCount = 0;
	zannzou = 0;

	srand((unsigned int)time(0));

	//敵を生存状態にする
	isLive = TRUE;

	//オーディオクラスの動的作成
	audio = new Audio;

	//エフェクトクラスの動的作成
	efect = new Efect2D;
}

//――――――――――――――――――――――
//	デストラクタ
//――――――――――――――――――――――
Enemy::~Enemy()
{
	//オーディオクラスの削除
	SAFE_DELETE(audio);

	//エフェクトクラスの削除
	SAFE_DELETE(efect);
}

//機能：読み込み処理
//引数：なし
//戻値：成功か失敗か
HRESULT Enemy::Load()
{
	//エネミーの画像の読み込み
	if (FAILED(sprite.Load("pict\\enemy.png")))
	{
		return E_FAIL;	//失敗を返す
	}

	//オーディオクラスのロード関数を呼び出す
	if (FAILED(audio->Load("Sound\\Wave Bank.xwb", "Sound\\Sound Bank.xsb")))
	{
		return E_FAIL;		//失敗を返す
	}

	//エフェクトクラスのロード関数を呼び出す
	if (FAILED(efect->Load("pict\\bom.png", D3DXVECTOR2(64, 64), 0.2f)))
	{
		return E_FAIL;	//失敗を返す
	}

	return S_OK;		//成功を返す
}

//機能：更新処理
//引数：なし
//戻値：成功か失敗か
HRESULT Enemy::Update()
{
	//移動処理で失敗したら
	if (FAILED(Move()))
	{
		return E_FAIL;	//失敗を返す
	}

	return S_OK;		//成功を返す
}

//機能：描画処理
//引数：なし
//戻値：成功か失敗か
HRESULT Enemy::Render()
{
	//構造体を作成
	SpriteData data;
	data.scale = D3DXVECTOR2(0.25f, 0.25f);

	//生存状態のときだけ描画
	if (isLive == TRUE)
	{
		//敵の位置を代入
		data.pos.x = position.x;
		data.pos.y = position.y;

		sprite.Draw(&data);
	}

	efect->Draw();
	return S_OK;	//成功を返す
}

//機能：移動処理
//引数：なし
//戻値：成功か失敗か
HRESULT Enemy::Move()
{
	return S_OK;	//成功を返す
}

//機能：死亡したとき
//引数：なし
//戻値：成功か失敗か
void Enemy::Kill()
{
	isLive = FALSE;		//死亡状態にする
	DeathCount++;

	audio->Play("Bom");
	efect->Add(position - D3DXVECTOR3(32, 32, 0));	//爆発エフェクト
	position.x -=9999;	//絶対にぶつからない場所に移動させる

	move.x = 0;
	move.y = 0;


	//初期位置
	position.x = 0;							//画面の１番左に表示
	position.y = rand() % 618 + 150;	//ランダムな縦位置に表示
	action = rand() % 10;
	zannzou = rand() % 2;

	//敵を生存状態にする
	isLive = TRUE;
}

HRESULT Enemy::Hit(UnitBase* pTarget)
{
	//移動速度
	if (typeid(*pTarget) == typeid(Player))
	{
		Player* player = (Player*)pTarget;

		

		if (action == 0 || action == 2 || action == 4 || action == 6 || action == 8)
		{
			//敵の位置情報取得
			D3DXVECTOR3 playerPos = player->GetPos();
			D3DXVECTOR3 move = position - playerPos;
			D3DXVec3Normalize(&move, &move);
			move *= 5;
			position -= move * (1.00 + (DeathCount / 200));

			if (position.x >= 200)
			{
				position.y += 15;
			}
			if (position.x >= 400)
			{
				position.y -= 30;
			}
			if (position.x >= 600)
			{
				position.y += 15;
			}
			position -= move;
		}
		if (action == 1 || action == 3 || action == 5 || action == 7)
		{
			//敵の位置情報取得
			D3DXVECTOR3 playerPos = player->GetPos();
			D3DXVECTOR3 move = position - playerPos;
			D3DXVec3Normalize(&move, &move);
			move *= 10;
			position -= move * (1.00 + (DeathCount / 200));

			if (position.x >= 200)
			{
				position.y += 15;
			}
			if (position.x >= 400)
			{
				position.y -= 30;
			}
			position -= move;
		}

		if (action == 9)
		{
			

			//敵の位置情報取得
			D3DXVECTOR3 playerPos = player->GetPos();
			D3DXVECTOR3 move = position - playerPos;
			D3DXVec3Normalize(&move, &move);
			move *= 5;
			position -= move * (1.00 + (DeathCount / 100));

			if (zannzou == 1)
			{
				if (position.x >= 550)
				{
					//初期位置
					position.x = 0;							//画面の１番左に表示
					position.y = rand() % 618 + 150;	//ランダムな縦位置に表示
					action = 1;

					//敵を生存状態にする
					isLive = TRUE;
				}
			}
		}
	}
	return S_OK;
}