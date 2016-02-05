/*===========================================================================================
�T�@���F�`���[�g���A���N���X�w�b�_�[�쐬
�쐬���F01��22��
�X�V���F
����ҁFYu Nishimukai
=============================================================================================*/
#pragma once

//---------------�C���N���[�h-----------------------
#include "UnitBase.h" 
#include "Sprite.h"
#include "Audio.h"

class Tutorial : public UnitBase
{
	//�I�[�f�B�I�N���X�̃I�u�W�F�N�g�쐬
	Audio* audio;

	//�X�v���C�g�N���X�̃I�u�W�F�N�g�쐬
	Sprite sprite;


public:
	Tutorial();		//�R���X�g���N�^
	~Tutorial();		//�f�X�g���N�^

	//�摜�ǂݍ���
	HRESULT Load();

	//�`�揈��
	HRESULT Render();

	//�X�V����
	HRESULT Update();
};


