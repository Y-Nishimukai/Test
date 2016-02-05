/*===========================================================================================
概　略：プレイヤー処理の関数定義
作成日：10月26日
更新日：
制作者：Yu Nishimukai
=============================================================================================*/

//---------------インクルード-----------------------
#include "Player.h"
#include "Enemy.h"

//――――――――――――――――――――――
//	コンストラクタ
//――――――――――――――――――――――
Player::Player()
{
	//プレイヤーの位置の初期化
	position.x = WINDOW_WIDTH - 192;
	position.y = WINDOW_HEIGHT - 384;

	//初期化
	attackCount = 0;
	isCutKeyFlg = FALSE;
	killCount = 0;
	bgm_flg = TRUE;
	stick_flg = FALSE;
	anime1 = 1;
	anime10 = 1;
	anime100 = 1;
	CutCnt = 1;

	status = STATUS_NOMAL;		//通常状態

	//オーディオクラスの動的作成
	audio = new Audio;

	//エフェクトクラスの動的作成
	efect = new Efect2D;
}

//――――――――――――――――――――――
//	デストラクタ
//――――――――――――――――――――――
Player::~Player()
{
	//オーディオクラスの削除
	SAFE_DELETE(audio);

	//エフェクトクラスの削除
	SAFE_DELETE(efect);
}

//機能：読み込み処理
//引数：なし
//戻値：成功か失敗か
HRESULT Player::Load()
{

	//プレイヤーの画像の読み込み
	if (FAILED(sprite.Load("pict\\CHaraNeko2.png")))
	{
		return E_FAIL;	//失敗を返す
	}

	//プレイヤーの画像の読み込み
	if (FAILED(spriteA.Load("pict\\CharaNeko1.png")))
	{
		return E_FAIL;	//失敗を返す
	}

	//数字の画像の読み込み
	if (FAILED(spriteNum.Load("pict\\number.png")))
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
HRESULT Player::Update()
{
	anime1 = killCount + 1;
	if (anime1 == 11)
	{
		anime10 += 1;
		killCount = 0;
	}
	if (anime10 == 11)
	{
		anime100 += 1;
		anime10 -= 10;
	}

	switch (status)
	{
		//通常状態のとき
	case STATUS_NOMAL:

		//ショットを撃つ
		if (FAILED(Cut()))
		{
			return E_FAIL;	//失敗を返す
		}

		break;
	}

	//フラグがTRUEのときだけBgm関数を呼べるようにすることでBGMをちゃんと鳴らせるようにする
	if (bgm_flg == TRUE)
	{
		Bgm();	//Bgm関数を呼び出す
	}

	////引数の型が敵だったら処理をする
	//if (typeid(*pTarget) == typeid(Enemy))
	//{
	//	Enemy* pEnemy = (Enemy*)pTarget;
	//	//敵の位置情報取得
	//	BOOL enemyLive = pEnemy->GetLive();
	//	if (enemyLive == FALSE)
	//	{
	//		isCutKeyFlg = FALSE;
	//	}
	//}

	return S_OK;		//成功を返す
}

//機能：描画処理
//引数：なし
//戻値：成功か失敗か
HRESULT Player::Render()
{
	//構造体を作成
	SpriteData data;

	//プレイヤーの位置を代入
	data.pos.x = position.x - 192;
	data.pos.y = position.y - 52.5 * 3;

	//プレイヤーの画像位置
	data.cut.x = 0;
	data.cut.y = 0;
	data.size.x = 192;
	data.size.y = 210;
	data.scale = D3DXVECTOR2(2.0f, 2.0f);
	

	//構造体を作成
	SpriteData dataN1;

	//カウンターの一の位の位置を代入
	dataN1.pos.x = WINDOW_WIDTH - 100;
	dataN1.pos.y = WINDOW_HEIGHT - 740;

	//カウンターの一の位の画像位置
	dataN1.cut.x = 46.6f * anime1;
	dataN1.cut.y = 0;
	dataN1.size.x = 46.6f;
	dataN1.size.y = 59;
	dataN1.scale = D3DXVECTOR2(1.5f, 1.5f);

	spriteNum.Draw(&dataN1);	//スプライトクラスの描画処理を呼んで変更したものを反映させる


	//構造体を作成
	SpriteData dataN10;

	//カウンターの十の位の位置を代入
	dataN10.pos.x = WINDOW_WIDTH - 175;
	dataN10.pos.y = WINDOW_HEIGHT - 740;

	//カウンターの十の位の画像位置
	dataN10.cut.x = 46.6f * anime10;
	dataN10.cut.y = 0;
	dataN10.size.x = 46.6f;
	dataN10.size.y = 59;
	dataN10.scale = D3DXVECTOR2(1.5f, 1.5f);

	spriteNum.Draw(&dataN10);	//スプライトクラスの描画処理を呼んで変更したものを反映させる

	
	//構造体を作成
	SpriteData dataN100;

	//カウンターの百の位の位置を代入
	dataN100.pos.x = WINDOW_WIDTH - 250;
	dataN100.pos.y = WINDOW_HEIGHT - 740;

	//カウンターの百の位の画像位置
	dataN100.cut.x = 46.6f * anime100;
	dataN100.cut.y = 0;
	dataN100.size.x = 46.6f;
	dataN100.size.y = 59;
	dataN100.scale = D3DXVECTOR2(1.5f, 1.5f);

	spriteNum.Draw(&dataN100);	//スプライトクラスの描画処理を呼んで変更したものを反映させる

	switch (status)
	{
		//通常状態の時
	case STATUS_NOMAL:

		sprite.Draw(&data);	//スプライトクラスの描画処理を呼んで変更したものを反映させる

		break;

	case STATUS_ATTACK:

		if (FAILED(Attack()))
		{
			return E_FAIL;		//失敗を返す
		}

		//構造体を作成
		SpriteData dataA;

		dataA.pos.x = position.x - 192;
		dataA.pos.y = position.y - 52.5 * 3;

		dataA.cut.x = 0;
		dataA.cut.y = 0;
		dataA.size.x = 192;
		dataA.size.y = 210;
		dataA.scale = D3DXVECTOR2(2.0f, 2.0f);

		spriteA.Draw(&dataA);	//スプライトクラスの描画処理を呼んで変更したものを反映させる

		break;
	}

	efect->Draw();
	return S_OK;	//成功を返す
}

//機能：衝突判定
//引数：ユニットベースクラスのポインタ（キャストで敵クラスに変換）
//戻値：成功か失敗か
HRESULT Player::Hit(UnitBase* pTarget)
{
	//引数の型が敵だったら処理をする
	if (typeid(*pTarget) == typeid(Enemy))
	{
		Enemy* pEnemy = (Enemy*)pTarget;
		//敵の位置情報取得
		D3DXVECTOR3 enemyPosition = pEnemy->GetPos();

		D3DXVECTOR3 dist;
		float dir;
		dist = enemyPosition - position;
		dir = D3DXVec3Length(&dist);

		switch (status)
		{
		case STATUS_NOMAL:
			//ぶつかっている
			if (dir <= 10)
			{
				g_gameScene = SC_END;
			}
			break;

		case STATUS_ATTACK:
			//攻撃範囲に敵がいる
			
			if (dir >= 11 && dir <= 200)
			{
				pEnemy->Kill();
				killCount++;
				CutCnt += 1;
			}
		}
	}

	return S_OK;	//成功を返す
}


//攻撃処理
//引数：なし
//戻値：成功か失敗か
HRESULT Player::Cut()
{
	//攻撃
	//ZキーかゲームパッドのAボタンが押されているときの処理
	if (g_pInput->IsKeyTap(DIK_Z) || g_pInput->IsPadButtonTap(XINPUT_GAMEPAD_A))
	{
		if (CutCnt == 1)
		{
			CutCnt -= 1;
			status = STATUS_ATTACK;	//攻撃状態にする
			attackCount = 0;
			//攻撃のときの効果音をだす
			audio->Play("Shot");
		}
	}
	return S_OK;	//成功を返す
}

//攻撃状態のときの処理
//引数：なし
//戻値：成功か失敗か
HRESULT Player::Attack()
{
	attackCount++;	//１フレームごとにカウントを＋１する

	//一定秒数経ったら操作を再度可能にする
	if (attackCount == RESURRECTION)
	{
		status = STATUS_NOMAL;	//通常状態に戻す
	}
	return S_OK;		//成功を返す
}

//機能：BGMを鳴らす
//引数：なし
//戻値：なし
void Player::Bgm()
{
	audio->Play("BGM");		//BGMを鳴らす
	bgm_flg = FALSE;		//この関数を呼ばれなくする
}