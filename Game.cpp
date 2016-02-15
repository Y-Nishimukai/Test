/*=======================================================================================================
概　略：ゲーム全体の流れを扱う処理
作成日：10月26日
更新日：
制作者：Yu Nishimukai
=======================================================================================================*/

//---------------インクルード-----------------------
#include "Game.h"
#include "TitleScene.h"
#include "TutorialScene.h"
#include "WaitingScene.h"
#include "PlayScene.h"
#include "ClearScene.h"

//----------------グローバル変数----------------
GAME_SCENE g_gameScene;				//現在のゲームシーン
LPDIRECT3DDEVICE9 g_pDevice;		//Direct3Dデバイスオブジェクト
Input*          g_pInput;			//入力処理オブジェクト
LPD3DXFONT g_pFont = NULL;


//――――――――――――――――――――――
//	コンストラクタ
//――――――――――――――――――――――
Game::Game()
{
	//各シーンオブジェクトの生成
	scene[SC_TITLE] = new TitleScene;		//タイトルシーン
	scene[SC_TUTORIAL] = new TutorialScene;
	scene[SC_WAITING] = new WaitingScene;
	scene[SC_PLAY] = new PlayScene;		//プレイシーン
	scene[SC_END] = new ClearScene;

	//最初はタイトルシーン
	g_gameScene = SC_TITLE;
}

//――――――――――――――――――――――
//	デストラクタ
//――――――――――――――――――――――
Game::~Game()
{
	for (int i = 0; i < SC_MAX; i++)
	{
		delete scene[i];
	}

	//DirectX開放
	SAFE_RELEASE(g_pDevice);	//デバイスオブジェクト
	SAFE_RELEASE(pD3d);			//Direct3Dオブジェクト
}

//――――――――――――――――――――――
// Direct3D初期化
//――――――――――――――――――――――
HRESULT Game::InitD3d(HWND hWnd)
{
	// 「Direct3D」オブジェクトの作成
	if (NULL == (pD3d = Direct3DCreate9(D3D_SDK_VERSION)))		//Direct3Dを作成して失敗してないか判定
	{
		MessageBox(0, "Direct3Dの作成に失敗しました", "", MB_OK);		//失敗していたらメッセージボックスで失敗を表示

		return E_FAIL;		//失敗したことを返す
	}


	// 「DIRECT3Dデバイス」オブジェクトの作成(構造体)
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));								//初期化
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;			//バックバッファのフォーマット
	d3dpp.BackBufferCount = 1;						//用意するバックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//スワップ
	d3dpp.Windowed = TRUE;					//ディスプレイ全体に絵を表示させたいときはFALSE
	d3dpp.EnableAutoDepthStencil = TRUE;					//Zバッファ(奥行き）を使う(TURE)か使わない(FALSE)か
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				//バッファのフォーマット

	//ゲーム画面の作成
	if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice)))				//環境によってはDirect3Dの作成に失敗する可能性があるためif文にする
	{
		//失敗したらメッセージボックスで知らせる
		MessageBox(0, "HALモードでDIRECT3Dデバイスを作成できません\nREFモードで再試行します", NULL, MB_OK);

		//パフォーマンスを落として再度作成
		if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice)))			//それでも失敗する可能性がある
		{
			//失敗を知らせる
			MessageBox(0, "DIRECT3Dデバイスの作成に失敗しました", NULL, MB_OK);
			return E_FAIL;			//失敗を返す
		}
	}

	return S_OK;	//成功を返す

}


//――――――――――――――――――――――
//	読み込み処理
//――――――――――――――――――――――
HRESULT Game::Load()
{
	//全てのシーンの読み込み
	for (int i = 0; i < SC_MAX; i++)
	{
		//どこかで失敗していたら
		if (FAILED(scene[i]->Load()))
		{
			return E_FAIL;	//失敗を返す（Main関数に）
		}
	}
	return S_OK;
}

//――――――――――――――――――――――
//	衝突判定
//――――――――――――――――――――――
HRESULT Game::Hit()
{
	//どこかで失敗していたら
	if (FAILED(scene[g_gameScene]->Hit()))
	{
		return E_FAIL;	//失敗していたら
	}
	return S_OK;	//成功を変えす
}

//――――――――――――――――――――――
//	更新処理
//――――――――――――――――――――――
HRESULT Game::Update()
{
	//入力処理の更新処理（キーの状態を調べる）
	g_pInput->Update();

	//どこかで失敗していたら
	if (FAILED(scene[g_gameScene]->Update()))
	{
		return E_FAIL;	//失敗を返す
	}
	return S_OK;	//成功を返す
}

//――――――――――――――――――――――
//	描画処理
//――――――――――――――――――――――
HRESULT Game::Render()
{
	//画面をクリア(XRGBで画面の色を青　ZBUFFERでzバッファもクリアにしている）
	g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pDevice->BeginScene()))		//DirectXだとここで失敗するときもあるので成功したか判定する
	{

		//ゲーム画面の描画
		if (FAILED(scene[g_gameScene]->Render()))	//どこかで失敗していたら
		{
			return E_FAIL;	//失敗を返す
		}

		//描画終了
		g_pDevice->EndScene();
		//BeginSceneとEndSceneはBeginPaintとEndPaintのようなイメージでよい
	}

	//フリップ
	//Direct3Dでは2枚の画面（フロントバッファ、バックバッファ）を用意してバックバッファのほうに画像を描画する
	//全ての画像を描画したら、バックバッファとフロントバッファを交換するこれをフリップという
	g_pDevice->Present(NULL, NULL, NULL, NULL);

	return S_OK;	//成功を返す
}

