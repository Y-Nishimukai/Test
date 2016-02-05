/*===========================================================================================
�T�@���F�`���[�g���A���N���X�̊֐���`
�쐬���F01��22��
�X�V���F
����ҁFYu Nishimukai
=============================================================================================*/

//---------------�C���N���[�h-----------------------
#include "Tutorial.h"


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�R���X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Tutorial::Tutorial()
{
	//�I�[�f�B�I�N���X�̓��I�쐬
	audio = new Audio;
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�f�X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Tutorial::~Tutorial()
{
	//�I�[�f�B�I�N���X�̍폜
	SAFE_DELETE(audio);
}

HRESULT Tutorial::Load()
{
	//�e�N�X�`���̍쐬�Ɏ��s�����Ƃ�y
	if (FAILED(sprite.Load("pict\\Tutorial.png")))
	{
		return E_FAIL;	//���s�������Ƃ�Ԃ�
	}

	//�I�[�f�B�I�N���X�̃��[�h�֐����Ăяo��
	if (FAILED(audio->Load("Sound\\Wave Bank.xwb", "Sound\\Sound Bank.xsb")))
	{
		return E_FAIL;		//���s��Ԃ�
	}



	return S_OK;	//�����������Ƃ�Ԃ�
}

//�@�\�F�X�V����
//�����F�Ȃ�
//�ߒl�F�������������s������
HRESULT Tutorial::Update()
{
	//�X�y�[�X�L�[�������ꂽ��
	if (g_pInput->IsKeyTap(DIK_SPACE))
	{
		//�v���C�V�[���Ɉڍs
		g_gameScene = SC_PLAY;
	}

	//A�{�^���������ꂽ��
	if (g_pInput->IsPadButtonTap(XINPUT_GAMEPAD_A))
	{
		//�v���C�V�[���Ɉڍs
		g_gameScene = SC_PLAY;
	}

	return S_OK;	//������m�点��
}


HRESULT Tutorial::Render()
{
	//�\���̂��쐬
	SpriteData data;

	sprite.Draw(&data);	//�X�v���C�g�N���X�̕`�揈�����Ă�ŕύX�������̂𔽉f������


	return S_OK;	//������Ԃ�
}