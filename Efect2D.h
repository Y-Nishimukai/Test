/*=======================================================================================================
�T�@���F�G�t�F�N�g����������
�쐬���F10��26��
�X�V���F
����ҁFYu Nishimukai
=======================================================================================================*/
#pragma once

//---------------�C���N���[�h-----------------------
#include "Sprite.h"
#include <List>

class Efect2D
{
	Sprite *spt;
	D3DXVECTOR2 size;	//�T�C�Y�p�̕ϐ�
	float Aspeed;		//�A�j���[�V�������x�p�̕ϐ�

	struct EffectData
	{
		float anime;		//�A�j���[�V�����p�̕ϐ�
		D3DXVECTOR3 position;	//�`��ʒu�̕ϐ�
	};

	std::list<EffectData> dataList;

public:
	Efect2D();
	~Efect2D();
	HRESULT Load(char* fileName, D3DXVECTOR2 s, float sp);
	void Draw();
	void Add(D3DXVECTOR3 pos);
};

