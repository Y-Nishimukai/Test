/*===========================================================================================
概　略：プレイヤー画面の背景の関数定義
作成日：10月26日
更新日：
制作者：Yu Nishimukai
=============================================================================================*/

//---------------インクルード-----------------------
#include "BackGround.h"

//――――――――――――――――――――――
//	コンストラクタ
//――――――――――――――――――――――
BackGround::BackGround()
{
}

//――――――――――――――――――――――
//	デストラクタ
//――――――――――――――――――――――
BackGround::~BackGround()
{
}

//機能：読み込み処理
//引数：なし
//戻値：成功か失敗か
HRESULT BackGround::Load()
{
	//背景画像読み込み
	if (FAILED(sprite.Load("pict\\background.bmp")))
	{
		return E_FAIL;		//失敗を返す
	}

	if (FAILED(spriteB.Load("pict\\brock.jpg")))
	{
		return E_FAIL;		//失敗を返す
	}

	return S_OK;			//成功を返す
}

//機能：描画処理
//引数：なし
//戻値：成功か失敗か
HRESULT BackGround::Render()
{
	//構造体を作成
	SpriteData data;
	

	sprite.Draw(&data);	//スプライトクラスの描画処理を呼んで変更したものを反映させる

	SpriteData dataB;
	dataB.pos.x = 700;
	dataB.pos.y = 640;
	dataB.scale = D3DXVECTOR2(1.5f, 1.0f);

	spriteB.Draw(&dataB);


	return S_OK;	//成功を返す
}
