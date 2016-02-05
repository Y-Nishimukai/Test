/*=======================================================================================================
�T�@���F�G�t�F�N�g����������
�쐬���F10��26��
�X�V���F
����ҁFYu Nishimukai
=======================================================================================================*/

//---------------�C���N���[�h-----------------------
#include "Efect2D.h"

Efect2D::Efect2D()
{
	spt = 0;

	//�X�v���C�g�N���X�̓��I�쐬
	spt = new Sprite;

	size = D3DXVECTOR2(64, 64);			//�����̃T�C�Y
	Aspeed = 0.2f;						//�������x
}


Efect2D::~Efect2D()
{
	dataList.clear();

	//�X�v���C�g�N���X�̍폜
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

//�����`��
void Efect2D::Draw()
{
	SpriteData data;
	data.size = size;
	data.scale = D3DXVECTOR2(2, 2);

	std::list<EffectData>::iterator itr;		//�C�e���[�^

	for (itr = dataList.begin(); itr != dataList.end();)
	{
		data.pos = (*itr).position;			//�����ʒu
		data.cut.x = (int)(*itr).anime * data.size.x;
		spt->Draw(&data);
		(*itr).anime += Aspeed;			//�������x

		D3DXVECTOR2 pictSize = spt->GetSize();

		if ((*itr).anime > pictSize.x / data.size.x)
		{
			//�G�t�F�N�g�I��
			itr = dataList.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

//�ʒu��n��
void Efect2D::Add(D3DXVECTOR3 pos)
{
	EffectData d;
	d.anime = 0;
	d.position = pos;
	dataList.push_back(d);
}