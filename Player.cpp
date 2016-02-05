/*===========================================================================================
�T�@���F�v���C���[�����̊֐���`
�쐬���F10��26��
�X�V���F
����ҁFYu Nishimukai
=============================================================================================*/

//---------------�C���N���[�h-----------------------
#include "Player.h"
#include "Enemy.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�R���X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Player::Player()
{
	//�v���C���[�̈ʒu�̏�����
	position.x = WINDOW_WIDTH - 192;
	position.y = WINDOW_HEIGHT - 384;

	//������
	attackCount = 0;
	isCutKeyFlg = FALSE;
	killCount = 0;
	bgm_flg = TRUE;
	stick_flg = FALSE;
	anime1 = 1;
	anime10 = 1;
	anime100 = 1;
	CutCnt = 1;

	status = STATUS_NOMAL;		//�ʏ���

	//�I�[�f�B�I�N���X�̓��I�쐬
	audio = new Audio;

	//�G�t�F�N�g�N���X�̓��I�쐬
	efect = new Efect2D;
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�f�X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Player::~Player()
{
	//�I�[�f�B�I�N���X�̍폜
	SAFE_DELETE(audio);

	//�G�t�F�N�g�N���X�̍폜
	SAFE_DELETE(efect);
}

//�@�\�F�ǂݍ��ݏ���
//�����F�Ȃ�
//�ߒl�F���������s��
HRESULT Player::Load()
{

	//�v���C���[�̉摜�̓ǂݍ���
	if (FAILED(sprite.Load("pict\\CHaraNeko2.png")))
	{
		return E_FAIL;	//���s��Ԃ�
	}

	//�v���C���[�̉摜�̓ǂݍ���
	if (FAILED(spriteA.Load("pict\\CharaNeko1.png")))
	{
		return E_FAIL;	//���s��Ԃ�
	}

	//�����̉摜�̓ǂݍ���
	if (FAILED(spriteNum.Load("pict\\number.png")))
	{
		return E_FAIL;	//���s��Ԃ�
	}

	//�I�[�f�B�I�N���X�̃��[�h�֐����Ăяo��
	if (FAILED(audio->Load("Sound\\Wave Bank.xwb", "Sound\\Sound Bank.xsb")))
	{
		return E_FAIL;		//���s��Ԃ�
	}

	//�G�t�F�N�g�N���X�̃��[�h�֐����Ăяo��
	if (FAILED(efect->Load("pict\\bom.png", D3DXVECTOR2(64, 64), 0.2f)))
	{
		return E_FAIL;	//���s��Ԃ�
	}

	return S_OK;		//������Ԃ�
}

//�@�\�F�X�V����
//�����F�Ȃ�
//�ߒl�F���������s��
HRESULT Player::Update()
{
	anime1 = killCount + 1;
	if (anime1 == 11)
	{
		anime10 += 1;
		killCount = 0;
	}
	if (anime10 == 11)
	{
		anime100 += 1;
		anime10 -= 10;
	}

	switch (status)
	{
		//�ʏ��Ԃ̂Ƃ�
	case STATUS_NOMAL:

		//�V���b�g������
		if (FAILED(Cut()))
		{
			return E_FAIL;	//���s��Ԃ�
		}

		break;
	}

	//�t���O��TRUE�̂Ƃ�����Bgm�֐����Ăׂ�悤�ɂ��邱�Ƃ�BGM�������Ɩ点��悤�ɂ���
	if (bgm_flg == TRUE)
	{
		Bgm();	//Bgm�֐����Ăяo��
	}

	////�����̌^���G�������珈��������
	//if (typeid(*pTarget) == typeid(Enemy))
	//{
	//	Enemy* pEnemy = (Enemy*)pTarget;
	//	//�G�̈ʒu���擾
	//	BOOL enemyLive = pEnemy->GetLive();
	//	if (enemyLive == FALSE)
	//	{
	//		isCutKeyFlg = FALSE;
	//	}
	//}

	return S_OK;		//������Ԃ�
}

//�@�\�F�`�揈��
//�����F�Ȃ�
//�ߒl�F���������s��
HRESULT Player::Render()
{
	//�\���̂��쐬
	SpriteData data;

	//�v���C���[�̈ʒu����
	data.pos.x = position.x - 192;
	data.pos.y = position.y - 52.5 * 3;

	//�v���C���[�̉摜�ʒu
	data.cut.x = 0;
	data.cut.y = 0;
	data.size.x = 192;
	data.size.y = 210;
	data.scale = D3DXVECTOR2(2.0f, 2.0f);
	

	//�\���̂��쐬
	SpriteData dataN1;

	//�J�E���^�[�̈�̈ʂ̈ʒu����
	dataN1.pos.x = WINDOW_WIDTH - 100;
	dataN1.pos.y = WINDOW_HEIGHT - 740;

	//�J�E���^�[�̈�̈ʂ̉摜�ʒu
	dataN1.cut.x = 46.6f * anime1;
	dataN1.cut.y = 0;
	dataN1.size.x = 46.6f;
	dataN1.size.y = 59;
	dataN1.scale = D3DXVECTOR2(1.5f, 1.5f);

	spriteNum.Draw(&dataN1);	//�X�v���C�g�N���X�̕`�揈�����Ă�ŕύX�������̂𔽉f������


	//�\���̂��쐬
	SpriteData dataN10;

	//�J�E���^�[�̏\�̈ʂ̈ʒu����
	dataN10.pos.x = WINDOW_WIDTH - 175;
	dataN10.pos.y = WINDOW_HEIGHT - 740;

	//�J�E���^�[�̏\�̈ʂ̉摜�ʒu
	dataN10.cut.x = 46.6f * anime10;
	dataN10.cut.y = 0;
	dataN10.size.x = 46.6f;
	dataN10.size.y = 59;
	dataN10.scale = D3DXVECTOR2(1.5f, 1.5f);

	spriteNum.Draw(&dataN10);	//�X�v���C�g�N���X�̕`�揈�����Ă�ŕύX�������̂𔽉f������

	
	//�\���̂��쐬
	SpriteData dataN100;

	//�J�E���^�[�̕S�̈ʂ̈ʒu����
	dataN100.pos.x = WINDOW_WIDTH - 250;
	dataN100.pos.y = WINDOW_HEIGHT - 740;

	//�J�E���^�[�̕S�̈ʂ̉摜�ʒu
	dataN100.cut.x = 46.6f * anime100;
	dataN100.cut.y = 0;
	dataN100.size.x = 46.6f;
	dataN100.size.y = 59;
	dataN100.scale = D3DXVECTOR2(1.5f, 1.5f);

	spriteNum.Draw(&dataN100);	//�X�v���C�g�N���X�̕`�揈�����Ă�ŕύX�������̂𔽉f������

	switch (status)
	{
		//�ʏ��Ԃ̎�
	case STATUS_NOMAL:

		sprite.Draw(&data);	//�X�v���C�g�N���X�̕`�揈�����Ă�ŕύX�������̂𔽉f������

		break;

	case STATUS_ATTACK:

		if (FAILED(Attack()))
		{
			return E_FAIL;		//���s��Ԃ�
		}

		//�\���̂��쐬
		SpriteData dataA;

		dataA.pos.x = position.x - 192;
		dataA.pos.y = position.y - 52.5 * 3;

		dataA.cut.x = 0;
		dataA.cut.y = 0;
		dataA.size.x = 192;
		dataA.size.y = 210;
		dataA.scale = D3DXVECTOR2(2.0f, 2.0f);

		spriteA.Draw(&dataA);	//�X�v���C�g�N���X�̕`�揈�����Ă�ŕύX�������̂𔽉f������

		break;
	}

	efect->Draw();
	return S_OK;	//������Ԃ�
}

//�@�\�F�Փ˔���
//�����F���j�b�g�x�[�X�N���X�̃|�C���^�i�L���X�g�œG�N���X�ɕϊ��j
//�ߒl�F���������s��
HRESULT Player::Hit(UnitBase* pTarget)
{
	//�����̌^���G�������珈��������
	if (typeid(*pTarget) == typeid(Enemy))
	{
		Enemy* pEnemy = (Enemy*)pTarget;
		//�G�̈ʒu���擾
		D3DXVECTOR3 enemyPosition = pEnemy->GetPos();

		D3DXVECTOR3 dist;
		float dir;
		dist = enemyPosition - position;
		dir = D3DXVec3Length(&dist);

		switch (status)
		{
		case STATUS_NOMAL:
			//�Ԃ����Ă���
			if (dir <= 10)
			{
				g_gameScene = SC_END;
			}
			break;

		case STATUS_ATTACK:
			//�U���͈͂ɓG������
			
			if (dir >= 11 && dir <= 200)
			{
				pEnemy->Kill();
				killCount++;
				CutCnt += 1;
			}
		}
	}

	return S_OK;	//������Ԃ�
}


//�U������
//�����F�Ȃ�
//�ߒl�F���������s��
HRESULT Player::Cut()
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
HRESULT Player::Attack()
{
	attackCount++;	//�P�t���[�����ƂɃJ�E���g���{�P����

	//���b���o�����瑀����ēx�\�ɂ���
	if (attackCount == RESURRECTION)
	{
		status = STATUS_NOMAL;	//�ʏ��Ԃɖ߂�
	}
	return S_OK;		//������Ԃ�
}

//�@�\�FBGM��炷
//�����F�Ȃ�
//�ߒl�F�Ȃ�
void Player::Bgm()
{
	audio->Play("BGM");		//BGM��炷
	bgm_flg = FALSE;		//���̊֐����Ă΂�Ȃ�����
}