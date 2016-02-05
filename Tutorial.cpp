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
	//スペースキーが押されたら
	if (g_pInput->IsKeyTap(DIK_SPACE))
	{
		//プレイシーンに移行
		g_gameScene = SC_PLAY;
	}

	//Aボタンが押されたら
	if (g_pInput->IsPadButtonTap(XINPUT_GAMEPAD_A))
	{
		//プレイシーンに移行
		g_gameScene = SC_PLAY;
	}

	return S_OK;	//成功を知らせる
}


HRESULT Tutorial::Render()
{
	//構造体を作成
	SpriteData data;

	sprite.Draw(&data);	//スプライトクラスの描画処理を呼んで変更したものを反映させる


	return S_OK;	//成功を返す
}