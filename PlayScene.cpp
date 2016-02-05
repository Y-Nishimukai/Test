/*===========================================================================================
概　略：プレイシーンを扱う処理
作成日：10月26日
更新日：
制作者：Yu Nishimukai
=============================================================================================*/

//---------------インクルード-----------------------
#include "PlayScene.h"
#include "Player.h"		//プレイヤークラス
#include "Enemy.h"		//敵クラス
#include "BackGround.h"	//背景クラス

//――――――――――――――――――――――
//	コンストラクタ
//――――――――――――――――――――――
PlayScene::PlayScene()
{
	unit.push_back(new BackGround);

	//ユニットを追加
	unit.push_back(new Player);		//プレイヤークラスを追加

	unit.push_back(new Enemy);		//敵クラスを追加
}

HRESULT PlayScene::Update()
{

	unit.push_back(new Enemy);

	return S_OK;
}
