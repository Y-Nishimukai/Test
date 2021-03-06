/*===========================================================================================
概　略：チュートリアルクラスの関数定義
作成日：01月22日
更新日：
制作者：Yu Nishimukai
=============================================================================================*/

//---------------インクルード-----------------------
#include "Tutorial.h"


//――――――――――――――――――――――
//	コンストラクタ
//――――――――――――――――――――――
Tutorial::Tutorial()
{
	//プレイヤーの位置の初期化
	position.x = WINDOW_WIDTH - 192;
	position.y = WINDOW_HEIGHT - 384;

	attackCount = 0;
	isCutKeyFlg = FALSE;
	CutCnt = 1;

	//オーディオクラスの動的作成
	audio = new Audio;
}

//――――――――――――――――――――――
//	デストラクタ
//――――――――――――――――――――――
Tutorial::~Tutorial()
{
	//オーディオクラスの削除
	SAFE_DELETE(audio);
}

HRESULT Tutorial::Load()
{
	//プレイヤーの画像の読み込み
	if (FAILED(sprite1.Load("pict\\CHaraNeko2.png")))
	{
		return E_FAIL;	//失敗を返す
	}

	//プレイヤーの画像の読み込み
	if (FAILED(sprite2.Load("pict\\CharaNeko1.png")))
	{
		return E_FAIL;	//失敗を返す
	}

	//背景画像読み込み
	if (FAILED(spriteA.Load("pict\\background2.bmp")))
	{
		return E_FAIL;		//失敗を返す
	}

	if (FAILED(spriteB.Load("pict\\brock.jpg")))
	{
		return E_FAIL;		//失敗を返す
	}

	//テクスチャの作成に失敗したときy
	if (FAILED(sprite.Load("pict\\Tutorial.png")))
	{
		return E_FAIL;	//失敗したことを返す
	}

	//オーディオクラスのロード関数を呼び出す
	if (FAILED(audio->Load("Sound\\Wave Bank.xwb", "Sound\\Sound Bank.xsb")))
	{
		return E_FAIL;		//失敗を返す
	}



	return S_OK;	//成功したことを返す
}

//機能：更新処理
//引数：なし
//戻値：成功したか失敗したか
HRESULT Tutorial::Update()
{
	switch (status)
	{
		//通常状態のとき
	case STATUS_NOMAL:

		//攻撃をする
		if (FAILED(Cut()))
		{
			return E_FAIL;	//失敗を返す
		}

		break;
	}

	//スペースキーが押されたら
	if (g_pInput->IsKeyTap(DIK_SPACE))
	{
		//プレイシーンに移行
		g_gameScene = SC_WAITING;
	}

	//Aボタンが押されたら
	if (g_pInput->IsPadButtonTap(XINPUT_GAMEPAD_A))
	{
		//プレイシーンに移行
		g_gameScene = SC_WAITING;
	}

	return S_OK;	//成功を知らせる
}


HRESULT Tutorial::Render()
{
	//構造体を作成
	SpriteData data;

	spriteA.Draw(&data);	//スプライトクラスの描画処理を呼んで変更したものを反映させる

	SpriteData dataB;
	dataB.pos.x = 700;
	dataB.pos.y = 640;
	dataB.scale = D3DXVECTOR2(1.5f, 1.0f);

	spriteB.Draw(&dataB);

	//構造体を作成
	SpriteData data1;

	//プレイヤーの位置を代入
	data1.pos.x = position.x - 192;
	data1.pos.y = position.y - 52.5 * 3;

	//プレイヤーの画像位置
	data1.cut.x = 0;
	data1.cut.y = 0;
	data1.size.x = 192;
	data1.size.y = 210;
	data1.scale = D3DXVECTOR2(2.0f, 2.0f);

	switch (status)
	{
		//通常状態の時
	case STATUS_NOMAL:

		sprite1.Draw(&data1);	//スプライトクラスの描画処理を呼んで変更したものを反映させる

		break;

	case STATUS_ATTACK:

		if (FAILED(Attack()))
		{
			return E_FAIL;		//失敗を返す
		}

		//構造体を作成
		SpriteData data2;

		data2.pos.x = position.x - 192;
		data2.pos.y = position.y - 52.5 * 3;

		data2.cut.x = 0;
		data2.cut.y = 0;
		data2.size.x = 192;
		data2.size.y = 210;
		data2.scale = D3DXVECTOR2(2.0f, 2.0f);

		sprite2.Draw(&data2);	//スプライトクラスの描画処理を呼んで変更したものを反映させる

		break;
	}

	


	return S_OK;	//成功を返す
}

//攻撃処理
//引数：なし
//戻値：成功か失敗か
HRESULT Tutorial::Cut()
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
HRESULT Tutorial::Attack()
{
	attackCount++;	//１フレームごとにカウントを＋１する

	//一定秒数経ったら操作を再度可能にする
	if (attackCount == RESURRECTION)
	{
		status = STATUS_NOMAL;	//通常状態に戻す
		CutCnt += 1;
	}
	return S_OK;		//成功を返す
}