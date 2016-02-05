/*===========================================================================================
�T�@���F�v���C���[�����̃w�b�_�[�쐬
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

//�萔��`
#define MOVE_SPEED 7	//�ړ����x
#define SHOT_LIMIT 1	//�e�̌��Ă���
#define RESURRECTION 5	//�������鎞��

//���j�b�g�x�[�X�N���X�̌p��
class Player : public UnitBase
{
	//�I�[�f�B�I�N���X�̃I�u�W�F�N�g�쐬
	Audio* audio;

	//�X�v���C�g�N���X�̃I�u�W�F�N�g�쐬
	Sprite sprite;

	Sprite spriteA;

	Sprite spriteNum;

	//�G�t�F�N�g�N���X�̃I�u�W�F�N�g�쐬
	Efect2D* efect;

	BOOL bgm_flg;		//BGM��炵�����̃t���O
	BOOL stick_flg;		//�X�e�B�b�N��|�������̃t���O

	int anime1;
	int anime10;
	int anime100;

	//�v���C���[�̏�Ԃ�萔��
	enum
	{
		STATUS_NOMAL,		//�ʏ�
		STATUS_ATTACK,		//�U��
	};
	int status;				//���݂̏��


	int attackCount;			//�U�����Ă���̎��Ԃ��J�E���g

	BOOL isCutKeyFlg;		//�U���{�^����������
	int killCount;			//�G�����̓|������������
	int CutCnt;

	//private�֐�
	HRESULT Cut();			//�U������
	HRESULT Attack();		//�U����ԏ���
	void Bgm();				//BGM��炷

public:
	Player();		//�R���X�g���N�^
	~Player();		//�f�X�g���N�^

	HRESULT Load();						//�ǂݍ��ݏ���
	HRESULT Update();					//�X�V����
	HRESULT Render();					//�`�揈��
	HRESULT Hit(UnitBase* pTarget);		//�Փˏ���

	D3DXVECTOR3 GetPlayer(){ return position; }
};

