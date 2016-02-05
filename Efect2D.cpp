/*=======================================================================================================
概　略：エフェクトを扱う処理
作成日：10月26日
更新日：
制作者：Yu Nishimukai
=======================================================================================================*/

//---------------インクルード-----------------------
#include "Efect2D.h"

Efect2D::Efect2D()
{
	spt = 0;

	//スプライトクラスの動的作成
	spt = new Sprite;

	size = D3DXVECTOR2(64, 64);			//爆発のサイズ
	Aspeed = 0.2f;						//爆発速度
}


Efect2D::~Efect2D()
{
	dataList.clear();

	//スプライトクラスの削除
	SAFE_DELETE(spt);
}

HRESULT Efect2D::Load(char* fileName, D3DXVECTOR2 sz, float sp)
{
	if (FAILED(spt->Load(fileName)))
	{
		return E_FAIL;
	}
	size = sz;
	Aspeed = sp;
	return S_OK;
}

//爆発描画
void Efect2D::Draw()
{
	SpriteData data;
	data.size = size;
	data.scale = D3DXVECTOR2(2, 2);

	std::list<EffectData>::iterator itr;		//イテレータ

	for (itr = dataList.begin(); itr != dataList.end();)
	{
		data.pos = (*itr).position;			//爆発位置
		data.cut.x = (int)(*itr).anime * data.size.x;
		spt->Draw(&data);
		(*itr).anime += Aspeed;			//爆発速度

		D3DXVECTOR2 pictSize = spt->GetSize();

		if ((*itr).anime > pictSize.x / data.size.x)
		{
			//エフェクト終了
			itr = dataList.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

//位置を渡す
void Efect2D::Add(D3DXVECTOR3 pos)
{
	EffectData d;
	d.anime = 0;
	d.position = pos;
	dataList.push_back(d);
}