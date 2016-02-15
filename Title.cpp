/*===========================================================================================
�T�@���F�^�C�g���N���X�̊֐���`
�쐬���F6��26��
�X�V���F6��26��
����ҁFYu Nishimukai
=============================================================================================*/

//---------------�C���N���[�h-----------------------
#include "Title.h"


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�R���X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Title::Title()
{
	lag = 0;
	isSpace = false;

	status = STATUS_NOMAL;		//�ʏ���

	//�I�[�f�B�I�N���X�̓��I�쐬
	audio = new Audio;
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�f�X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Title::~Title()
{
	//�I�[�f�B�I�N���X�̍폜
	SAFE_DELETE(audio);
}

HRESULT Title::Load()
{
	//�e�N�X�`���̍쐬�Ɏ��s�����Ƃ�y
	if (FAILED(sprite1.Load("pict\\Title1.png")))
	{
		return E_FAIL;	//���s�������Ƃ�Ԃ�
	}

	//�e�N�X�`���̍쐬�Ɏ��s�����Ƃ�y
	if (FAILED(sprite2.Load("pict\\Title2.png")))
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
HRESULT Title::Update()
{
	//�X�y�[�X�L�[�������ꂽ��
	if (g_pInput->IsKeyTap(DIK_SPACE))
	{
		status = STATUS_CUT;
		isSpace = true;
	}
	if (isSpace == true)
	{
		lag++;
		if (lag >= TIMELAG)
		{
			isSpace = false;
			//�`���[�g���A���V�[���Ɉڍs
			g_gameScene = SC_TUTORIAL;
		}
	}

	//A�{�^���������ꂽ��
	if (g_pInput->IsPadButtonTap(XINPUT_GAMEPAD_A))
	{
		//�v���C�V�[���Ɉڍs
		g_gameScene = SC_TUTORIAL;
	}

	return S_OK;	//������m�点��
}


HRESULT Title::Render()
{

	//�\���̂��쐬
	SpriteData data1;

	switch (status)
	{
		//�ʏ��Ԃ̎�
	case STATUS_NOMAL:

		sprite1.Draw(&data1);	//�X�v���C�g�N���X�̕`�揈�����Ă�ŕύX�������̂𔽉f������

		break;

	case STATUS_CUT:

		//�\���̂��쐬
		SpriteData data2;

		sprite2.Draw(&data2);	//�X�v���C�g�N���X�̕`�揈�����Ă�ŕύX�������̂𔽉f������

		break;
	}


	return S_OK;	//������Ԃ�
}

//HRESULT Title::Cut()
//{
//	lag++;	//�P�t���[�����ƂɃJ�E���g���{�P����
//
//	//���b���o�����瑀����ēx�\�ɂ���
//	if (lag == TIMELAG)
//	{
//		//�`���[�g���A���V�[���Ɉڍs
//		g_gameScene = SC_TUTORIAL;
//	}
//	return S_OK;		//������Ԃ�
//}