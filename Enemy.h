/*===========================================================================================
�T�@���F�G�l�~�[�����̃w�b�_�[�쐬
�쐬���F10��26��
�X�V���F
����ҁFYu Nishimukai
=============================================================================================*/
#pragma once

//---------------�C���N���[�h-----------------------
#include "UnitBase.h"
#include "Sprite.h"
#include "Audio.h"
#include "Efect2D.h"

//���j�b�g�x�[�X�N���X���p��
class Enemy : public UnitBase
{
	//�I�[�f�B�I�N���X�̃I�u�W�F�N�g�쐬
	Audio* audio;

	//�X�v���C�g�N���X�̃I�u�W�F�N�g�쐬
	Sprite sprite;

	//�G�t�F�N�g�N���X�̃I�u�W�F�N�g�쐬
	Efect2D* efect;

	POINT move;			//�ړ����x
	int action;
	int DeathCount;
	int zannzou;

	HRESULT Move();		//�ړ�

	BOOL  isLive;		//�����Ă���t���O�iFALSE�ɂȂ�Ǝ��S�j

public:
	Enemy();		//�R���X�g���N�^
	~Enemy();		//�f�X�g���N�^

	HRESULT Load();		//�ǂݍ��ݏ���
	HRESULT Hit(UnitBase* pTarget);
	HRESULT Update();	//�X�V����
	HRESULT Render();	//�`�揈��

	void Kill();		//�G�����S�����Ƃ�

	BOOL GetLive(){ return isLive; }
};

