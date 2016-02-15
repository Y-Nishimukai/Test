/*===========================================================================================
概　略：プロジェクト全体で必要なものをまとめたファイル
作成日：10月26日
更新日：
制作者：Yu Nishimukai
=============================================================================================*/
#pragma once

//---------------インクルード-----------------------
#include <windows.h>
#include <d3dx9.h>
#include "Input.h"


//----------ライブラリファイルのロード--------------
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

//-------------------定数宣言------------------
//ウィンドウサイズ
#define WINDOW_WIDTH	1024		//ウィンドウの幅
#define WINDOW_HEIGHT	768		//ウィンドウ高さ
#define ENEMY_LIMIT		  1		//敵の最大数
#define CHAR_SIZE		 32		//自機と敵のサイズ

//-------------------マクロ----------------------
#define SAFE_DELETE(p) {delete(p);	(p) = NULL;}					//動的に作ったモノを安全にデリートする
#define SAFE_DELETE_ARRAY(p) {delete[] (p);  (p) = NULL;}			//配列用
#define SAFE_RELEASE(p) {if(p != NULL){(p)->Release(); (p) = NULL;}}	//LP型用

//-------------------グローバル変数------------------
//シーン
enum GAME_SCENE
{
	SC_TITLE,	//タイトルシーン
	SC_TUTORIAL,
	SC_WAITING,
	SC_PLAY,	//プレイシーン
	SC_END,	//クリアシーン
	SC_MAX
};
extern GAME_SCENE	g_gameScene;		//実態はGame.cppで宣言

//Direct3Dデバイスオブジェクト
extern LPDIRECT3DDEVICE9 g_pDevice;

//入力処理オブジェクト
extern Input* g_pInput;	//クラスを作るときは基本的にポインタにした方が良い