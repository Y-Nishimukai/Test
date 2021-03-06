/*===========================================================================================
概　略：ゲームの入力処理を行うクラスヘッダー
作成日：10月26日
更新日：
制作者：Yu Nishimukai
=============================================================================================*/
#pragma once

#define DIRECTINPUT_VERSION 0x800 //DirectInput のバージョン設定

//---------------インクルード-----------------------
#include <dinput.h>
#include <XInput.h>	//コントローラ用のインクルード

//ライブラリ
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")	//インプットのバージョンは８で十分(DirectXと同じくらいのバージョンがあるが)
#pragma comment(lib,"Xinput.lib")	//コントローラ用

//マクロ
#define SAFE_RELEASE(p)        { if(p != NULL) { (p)->Release(); (p) = NULL; } }	//LP型変数の解放処理

class Input
{
	LPDIRECTINPUT8        pDinput;				//DirectInputオブジェクト
	LPDIRECTINPUTDEVICE8  pKeyDevice;			//デバイスオブジェクト（キーボード）
	XINPUT_STATE		  controllerState[4];     //コントローラーの状態(複数のコントローラを使いたいなら配列にする)
	XINPUT_STATE		  prevButtonState[4];		//前回のコントローラボタンの情報

	BYTE				  keyState[256];		//各キーの状態(キーが押されたか判断する場合はBYTE型にする使用)
	BYTE				  prevKeyState[256];	//前回のキーの情報

	BOOL connect[4];							//コントローラが接続されているか




public:
	Input();	//コンストラクタ
	~Input();	//デストラクタ

	HRESULT Init(HWND hWnd);			//DirectInputの準備

	HRESULT Update();					//各入力デバイスの状態を取得
	BOOL  IsKeyPush(DWORD keyCode);		//任意のキーが押されているかチェック
	BOOL  IsKeyTap(DWORD keyCode);		//任意のキーが押された瞬間かチェック
	BOOL  IsKeyRelease(DWORD keyCode);	//任意のキーが離されたかチェック

	//IDをいちいち指定させるのが面倒なのでそのときは引数に値を代入することで省略できる(デフォルト引数)

	BOOL  IsPadButtonPush(DWORD buttonCode, int ID = 0);			//コントローラーのボタンが押されているか
	BOOL IsPadButtonTap(DWORD buttonCode, int ID = 0);			//コントローラのボタンが押された瞬間か
	BOOL IsPadButtonRelease(DWORD buttonCode, int ID = 0);			//コントローラのボタンが離されたか

	float GetPadLStickX(int ID = 0);								//左スティックの左右の傾き
	float GetPadLStickY(int ID = 0);								//左スティックの上下の傾き
	float GetPadRStickX(int ID = 0);								//右スティックの左右の傾き
	float GetPadRStickY(int ID = 0);								//右スティックの上下の傾き
	float GetPadLTrigger(int ID = 0);								//左トリガーの押し込み
	float GetPadRTrigger(int ID = 0);								//右トリガーの押し込み

	void  Vibration(float leftSpeed, float rightSpeed, int ID = 0);     //振動エフェクト
};

