/*===========================================================================================
概　略：タイトルクラスの関数定義
作成日：6月26日
更新日：6月26日
制作者：Yu Nishimukai
=============================================================================================*/

//---------------インクルード-----------------------
#include "Title.h"


//――――――――――――――――――――――
//	コンストラクタ
//――――――――――――――――――――――
Title::Title()
{
	lag = 0;
	isSpace = false;

	status = STATUS_NOMAL;		//通常状態

	//オーディオクラスの動的作成
	audio = new Audio;
}

//――――――――――――――――――――――
//	デストラクタ
//――――――――――――――――――――――
Title::~Title()
{
	//オーディオクラスの削除
	SAFE_DELETE(audio);
}

HRESULT Title::Load()
{
	//テクスチャの作成に失敗したときy
	if (FAILED(sprite1.Load("pict\\Title1.png")))
	{
		return E_FAIL;	//失敗したことを返す
	}

	//テクスチャの作成に失敗したときy
	if (FAILED(sprite2.Load("pict\\Title2.png")))
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
HRESULT Title::Update()
{
	//スペースキーが押されたら
	if (g_pInput->IsKeyTap(DIK_SPACE))
	{
		status = STATUS_CUT;
		isSpace = true;
	}
	if (isSpace == true)
	{
		lag++;
		if (lag >= TIMELAG)
		{
			isSpace = false;
			//チュートリアルシーンに移行
			g_gameScene = SC_TUTORIAL;
		}
	}

	//Aボタンが押されたら
	if (g_pInput->IsPadButtonTap(XINPUT_GAMEPAD_A))
	{
		//プレイシーンに移行
		g_gameScene = SC_TUTORIAL;
	}

	return S_OK;	//成功を知らせる
}


HRESULT Title::Render()
{

	//構造体を作成
	SpriteData data1;

	switch (status)
	{
		//通常状態の時
	case STATUS_NOMAL:

		sprite1.Draw(&data1);	//スプライトクラスの描画処理を呼んで変更したものを反映させる

		break;

	case STATUS_CUT:

		//構造体を作成
		SpriteData data2;

		sprite2.Draw(&data2);	//スプライトクラスの描画処理を呼んで変更したものを反映させる

		break;
	}


	return S_OK;	//成功を返す
}

//HRESULT Title::Cut()
//{
//	lag++;	//１フレームごとにカウントを＋１する
//
//	//一定秒数経ったら操作を再度可能にする
//	if (lag == TIMELAG)
//	{
//		//チュートリアルシーンに移行
//		g_gameScene = SC_TUTORIAL;
//	}
//	return S_OK;		//成功を返す
//}