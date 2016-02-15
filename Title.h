/*===========================================================================================
�T�@���F�^�C�g���N���X�w�b�_�[�쐬
�쐬���F10��26��
�X�V���F
����ҁFYu Nishimukai
=============================================================================================*/
#pragma once

//---------------�C���N���[�h-----------------------
#include "UnitBase.h" 
#include "Sprite.h"
#include "Audio.h"

#define TIMELAG 60

class Title : public UnitBase
{
	//�I�[�f�B�I�N���X�̃I�u�W�F�N�g�쐬
	Audio* audio;

	//�X�v���C�g�N���X�̃I�u�W�F�N�g�쐬
	Sprite sprite1;

	Sprite sprite2;

	//�v���C���[�̏�Ԃ�萔��
	enum
	{
		STATUS_NOMAL,		//�ʏ�
		STATUS_CUT,		//�U��
	};
	int status;				//���݂̏��
	
	int lag;
	bool isSpace;

	HRESULT Cut();

public:
	Title();		//�R���X�g���N�^
	~Title();		//�f�X�g���N�^

	//�摜�ǂݍ���
	HRESULT Load();

	//�`�揈��
	HRESULT Render();

	//�X�V����
	HRESULT Update();
};


