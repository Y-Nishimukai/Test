/*===========================================================================================
概　略：各ゲームユニットの親クラス
作成日：10月26日
更新日：
制作者：Yu Nishimukai
=============================================================================================*/
#pragma once

//---------------インクルード-----------------------
#include "Global.h"
#include <typeinfo.h>


//―――――――――――――――――――――
//	各ゲームユニットの親クラス
//―――――――――――――――――――――
class UnitBase
{
protected:
	//ユニットの位置
	D3DXVECTOR3      position;

public:

	//デストラクタ
	virtual ~UnitBase() { };		//ここでvirtualにしとおかないと子クラスでデストラクタが呼ばれなくなる

	//読み込み処理
	virtual HRESULT Load();		//Direct3DはDirect3Dの準備が出来てからでないと画像の読み込みができない。
	//今まで通りだとSceneのコンストラクタで読みこんでいたがそれだと準備ができてない状態で読み込むのでエラーなる
	//ので別に読み込む用の関数を用意する

	//更新処理
	virtual HRESULT Update();

	//衝突判定処理
	//引数：pTarget	判定する相手ユニット
	virtual HRESULT Hit(UnitBase* pTarget);

	//描画処理
	//引数：hdc	デバイスコンテキストハンドル
	virtual HRESULT Render();

	//現在の位置を取得
	//戻値：現在の位置
	D3DXVECTOR3 GetPos()	{ return position; }
};

