/*===========================================================================================
�T�@���F�v���C���[��ʂ̔w�i�̃w�b�_�[�쐬
�쐬���F10��26��
�X�V���F
����ҁFYu Nishimukai
=============================================================================================*/
#pragma once

//---------------�C���N���[�h-----------------------
#include "UnitBase.h"
#include "Sprite.h"

//���j�b�g�x�[�X�N���X���p��
class BackGround : public UnitBase
{
	//�X�v���C�g�N���X�̃I�u�W�F�N�g�쐬
	Sprite sprite;

	Sprite spriteB;

public:
	BackGround();		//�R���X�g���N�^
	~BackGround();		//�f�X�g���N�^

	HRESULT Load();		//�ǂݍ��ݏ���
	HRESULT Render();	//�`�揈��
};
