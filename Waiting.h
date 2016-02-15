/*===========================================================================================
�T�@���F�ҋ@�N���X�w�b�_�[�쐬
�쐬���F02��12��
�X�V���F
����ҁFYu Nishimukai
=============================================================================================*/
#pragma once

//---------------�C���N���[�h-----------------------
#include "UnitBase.h" 
#include "Sprite.h"
#include "Audio.h"

#define RESURRECTION 5
#define WAITING 180	//�������鎞��

class Waiting : public UnitBase
{
	//�I�[�f�B�I�N���X�̃I�u�W�F�N�g�쐬
	Audio* audio;

	//�X�v���C�g�N���X�̃I�u�W�F�N�g�쐬
	Sprite sprite;

	Sprite sprite1;

	Sprite sprite2;

	Sprite spriteA;

	Sprite spriteB;

	Sprite spriteIti;

	Sprite spriteNi;

	Sprite spriteSan;

	//�v���C���[�̏�Ԃ�萔��
	enum
	{
		STATUS_NOMAL,		//�ʏ�
		STATUS_ATTACK,		//�U��
	};
	int status;				//���݂̏��

	int attackCount;			//�U�����Ă���̎��Ԃ��J�E���g
	int waiting;

	BOOL isWait;
	BOOL isCutKeyFlg;		//�U���{�^����������
	BOOL count3;
	BOOL count2;
	BOOL count1;
	int CutCnt;

	HRESULT Cut();			//�U������
	HRESULT Attack();		//�U����ԏ���


public:
	Waiting();		//�R���X�g���N�^
	~Waiting();		//�f�X�g���N�^

	//�摜�ǂݍ���
	HRESULT Load();

	//�`�揈��
	HRESULT Render();

	//�X�V����
	HRESULT Update();
};


