/*===========================================================================================
�T�@���F�N���A�N���X�w�b�_�[�쐬
�쐬���F10��26��
�X�V���F
����ҁFYu Nishimukai
=============================================================================================*/
#pragma once

//---------------�C���N���[�h-----------------------
#include "UnitBase.h"
#include "Sprite.h"

class Clear : public UnitBase
{
	//�X�v���C�g�N���X�̃I�u�W�F�N�g�쐬
	Sprite sprite;
	Sprite spriteG;
	Sprite spriteM;

public:
	Clear();	//�R���X�g���N�^
	~Clear();	//�f�X�g���N�^

	HRESULT Load();		//�ǂݍ��ݏ���
	HRESULT Update();	//�X�V����
	HRESULT Render();	//�`�揈��
};
