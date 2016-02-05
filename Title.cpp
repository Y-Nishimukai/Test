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
	if (FAILED(sprite.Load("pict\\Title.png")))
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
		//プレイシーンに移行
		g_gameScene = SC_TUTORIAL;
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
	SpriteData data;

	sprite.Draw(&data);	//スプライトクラスの描画処理を呼んで変更したものを反映させる


	return S_OK;	//成功を返す
}
