/*===========================================================================================
�T�@���F�ҋ@�N���X�̊֐���`
�쐬���F02��12��
�X�V���F
����ҁFYu Nishimukai
=============================================================================================*/

//---------------�C���N���[�h-----------------------
#include "Waiting.h"


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�R���X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Waiting::Waiting()
{
	//�v���C���[�̈ʒu�̏�����
	position.x = WINDOW_WIDTH - 192;
	position.y = WINDOW_HEIGHT - 384;

	attackCount = 0;
	isWait = false;
	isCutKeyFlg = FALSE;
	count3 = false;
	count2 = false;
	count1 = false;
	CutCnt = 1;

	//�I�[�f�B�I�N���X�̓��I�쐬
	audio = new Audio;
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�f�X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Waiting::~Waiting()
{
	//�I�[�f�B�I�N���X�̍폜
	SAFE_DELETE(audio);
}

HRESULT Waiting::Load()
{
	//�v���C���[�̉摜�̓ǂݍ���
	if (FAILED(sprite1.Load("pict\\CHaraNeko2.png")))
	{
		return E_FAIL;	//���s��Ԃ�
	}

	//�v���C���[�̉摜�̓ǂݍ���
	if (FAILED(sprite2.Load("pict\\CharaNeko1.png")))
	{
		return E_FAIL;	//���s��Ԃ�
	}

	//�w�i�摜�ǂݍ���
	if (FAILED(spriteA.Load("pict\\background.bmp")))
	{
		return E_FAIL;		//���s��Ԃ�
	}

	if (FAILED(spriteB.Load("pict\\brock.jpg")))
	{
		return E_FAIL;		//���s��Ԃ�
	}

	if (FAILED(spriteIti.Load("pict\\Count1.png")))
	{
		return E_FAIL;		//���s��Ԃ�
	}

	if (FAILED(spriteNi.Load("pict\\Count2.png")))
	{
		return E_FAIL;		//���s��Ԃ�
	}

	if (FAILED(spriteSan.Load("pict\\Count3.png")))
	{
		return E_FAIL;		//���s��Ԃ�
	}

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
HRESULT Waiting::Update()
{
	switch (status)
	{
		//�ʏ��Ԃ̂Ƃ�
	case STATUS_NOMAL:

		//�U��������
		if (FAILED(Cut()))
		{
			return E_FAIL;	//���s��Ԃ�
		}

		break;
	}

	isWait = true;
	if (isWait == true)
	{
		waiting++;
		if (waiting >= WAITING)
		{
			g_gameScene = SC_PLAY;
		}
	}

	
	return S_OK;	//������m�点��
}


HRESULT Waiting::Render()
{
	//�\���̂��쐬
	SpriteData data;

	spriteA.Draw(&data);	//�X�v���C�g�N���X�̕`�揈�����Ă�ŕύX�������̂𔽉f������

	SpriteData dataB;
	dataB.pos.x = 700;
	dataB.pos.y = 640;
	dataB.scale = D3DXVECTOR2(1.5f, 1.0f);

	spriteB.Draw(&dataB);

	//�\���̂��쐬
	SpriteData data1;

	//�v���C���[�̈ʒu����
	data1.pos.x = position.x - 192;
	data1.pos.y = position.y - 52.5 * 3;

	//�v���C���[�̉摜�ʒu
	data1.cut.x = 0;
	data1.cut.y = 0;
	data1.size.x = 192;
	data1.size.y = 210;
	data1.scale = D3DXVECTOR2(2.0f, 2.0f);

	switch (status)
	{
		//�ʏ��Ԃ̎�
	case STATUS_NOMAL:

		sprite1.Draw(&data1);	//�X�v���C�g�N���X�̕`�揈�����Ă�ŕύX�������̂𔽉f������

		break;

	case STATUS_ATTACK:

		if (FAILED(Attack()))
		{
			return E_FAIL;		//���s��Ԃ�
		}

		//�\���̂��쐬
		SpriteData data2;

		data2.pos.x = position.x - 192;
		data2.pos.y = position.y - 52.5 * 3;

		data2.cut.x = 0;
		data2.cut.y = 0;
		data2.size.x = 192;
		data2.size.y = 210;
		data2.scale = D3DXVECTOR2(2.0f, 2.0f);

		sprite2.Draw(&data2);	//�X�v���C�g�N���X�̕`�揈�����Ă�ŕύX�������̂𔽉f������

		break;
	}

	if (waiting <= 60)
	{
		count3 = true;
		if (count3 == true)
		{
			SpriteData dataSan;
			dataSan.pos.x = 350;
			dataSan.pos.y = 150;
			dataSan.scale = D3DXVECTOR2(2.0f, 2.0f);

			spriteSan.Draw(&dataSan);
		}
		count3 = false;
	}

	if (waiting >= 61 && waiting <= 120)
	{
		count2 = true;
		if (count2 == true)
		{
			SpriteData dataNi;
			dataNi.pos.x = 350;
			dataNi.pos.y = 150;
			dataNi.scale = D3DXVECTOR2(2.0f, 2.0f);

			spriteNi.Draw(&dataNi);
		}
		count2 = false;
	}

	if (waiting >= 121)
	{
		count1 = true;
		if (count1 == true)
		{
			SpriteData dataIti;
			dataIti.pos.x = 390;
			dataIti.pos.y = 150;
			dataIti.scale = D3DXVECTOR2(2.0f, 2.0f);

			spriteIti.Draw(&dataIti);
		}
		count1 = false;
	}

	return S_OK;	//������Ԃ�
}

//�U������
//�����F�Ȃ�
//�ߒl�F���������s��
HRESULT Waiting::Cut()
{
	//�U��
	//Z�L�[���Q�[���p�b�h��A�{�^����������Ă���Ƃ��̏���
	if (g_pInput->IsKeyTap(DIK_Z) || g_pInput->IsPadButtonTap(XINPUT_GAMEPAD_A))
	{
		if (CutCnt == 1)
		{
			CutCnt -= 1;
			status = STATUS_ATTACK;	//�U����Ԃɂ���
			attackCount = 0;
			//�U���̂Ƃ��̌��ʉ�������
			audio->Play("Shot");
		}
	}
	return S_OK;	//������Ԃ�
}

//�U����Ԃ̂Ƃ��̏���
//�����F�Ȃ�
//�ߒl�F���������s��
HRESULT Waiting::Attack()
{
	attackCount++;	//�P�t���[�����ƂɃJ�E���g���{�P����

	//���b���o�����瑀����ēx�\�ɂ���
	if (attackCount == RESURRECTION)
	{
		status = STATUS_NOMAL;	//�ʏ��Ԃɖ߂�
		CutCnt += 1;
	}
	return S_OK;		//������Ԃ�
}