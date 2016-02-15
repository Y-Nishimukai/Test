/*===========================================================================================
概　略：クリアクラスの関数定義
作成日：10月26日
更新日：
制作者：Yu Nishimukai
=============================================================================================*/

//---------------インクルード-----------------------
#include "Clear.h"
#include "Player.h"

//――――――――――――――――――――――
//	コンストラクタ
//――――――――――――――――――――――
Clear::Clear()
{
	position.x = 0;
	position.y = -192;

}

//――――――――――――――――――――――
//	デストラクタ
//――――――――――――――――――――――
Clear::~Clear()
{
}

//機能：読み込み処理
//引数：なし
//戻値；成功か失敗か
HRESULT Clear::Load()
{
	//クリア画像読み込み
	if (FAILED(sprite.Load("pict\\background.bmp")))
	{
		return E_FAIL;	//失敗を返す
	}

	if (FAILED(spriteG.Load("pict\\GAMEOVER.png")))
	{
		return E_FAIL;	//失敗を返す
	}

	if (FAILED(spriteM.Load("pict\\model.png")))
	{
		return E_FAIL;	//失敗を返す
	}

	return S_OK;		//成功を返す
}

//機能：更新処理
//引数：なし
//戻値：成功か失敗か
HRESULT Clear::Update()
{
	////スペースキーが押されたらタイトルシーンに
	//if (g_pInput->IsKeyTap(DIK_SPACE))
	//{
	//	g_gameScene = SC_TITLE;
	//}
	if (position.y <= 200)
	{
		position.y++;
	}

	return S_OK;		//成功を返す
}

//機能：描画処理
//引数：なし
//戻値：成功か失敗か
HRESULT Clear::Render()
{
	//構造体を作成
	SpriteData data;

	sprite.Draw(&data);	//スプライトクラスの描画処理を呼んで変更したものを反映させる

	SpriteData dataG;
	dataG.pos.y = position.y;

	spriteG.Draw(&dataG);

	SpriteData dataM;
	dataM.pos.y = 645;
	spriteM.Draw(&dataM);
	

	return S_OK;	//成功を返す

}