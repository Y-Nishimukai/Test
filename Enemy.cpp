/*===========================================================================================
�T�@���F�G�l�~�[�����̊֐���`
�쐬���F10��26��
�X�V���F
����ҁFYu Nishimukai
=============================================================================================*/

//---------------�C���N���[�h-----------------------
#include "Enemy.h"
#include "Player.h"
#include "stdlib.h"
#include "time.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�R���X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Enemy::Enemy()
{
	//�����ʒu
	position.x = 0;							//��ʂ̂P�ԍ��ɕ\��
	position.y = rand() % WINDOW_HEIGHT;	//�����_���ȏc�ʒu�ɕ\��

	action = 0;
	DeathCount = 0;
	zannzou = 0;

	srand((unsigned int)time(0));

	//�G�𐶑���Ԃɂ���
	isLive = TRUE;

	//�I�[�f�B�I�N���X�̓��I�쐬
	audio = new Audio;

	//�G�t�F�N�g�N���X�̓��I�쐬
	efect = new Efect2D;
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�f�X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Enemy::~Enemy()
{
	//�I�[�f�B�I�N���X�̍폜
	SAFE_DELETE(audio);

	//�G�t�F�N�g�N���X�̍폜
	SAFE_DELETE(efect);
}

//�@�\�F�ǂݍ��ݏ���
//�����F�Ȃ�
//�ߒl�F���������s��
HRESULT Enemy::Load()
{
	//�G�l�~�[�̉摜�̓ǂݍ���
	if (FAILED(sprite.Load("pict\\enemy.png")))
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
HRESULT Enemy::Update()
{
	//�ړ������Ŏ��s������
	if (FAILED(Move()))
	{
		return E_FAIL;	//���s��Ԃ�
	}

	return S_OK;		//������Ԃ�
}

//�@�\�F�`�揈��
//�����F�Ȃ�
//�ߒl�F���������s��
HRESULT Enemy::Render()
{
	//�\���̂��쐬
	SpriteData data;
	data.scale = D3DXVECTOR2(0.25f, 0.25f);

	//������Ԃ̂Ƃ������`��
	if (isLive == TRUE)
	{
		//�G�̈ʒu����
		data.pos.x = position.x;
		data.pos.y = position.y;

		sprite.Draw(&data);
	}

	efect->Draw();
	return S_OK;	//������Ԃ�
}

//�@�\�F�ړ�����
//�����F�Ȃ�
//�ߒl�F���������s��
HRESULT Enemy::Move()
{
	return S_OK;	//������Ԃ�
}

//�@�\�F���S�����Ƃ�
//�����F�Ȃ�
//�ߒl�F���������s��
void Enemy::Kill()
{
	isLive = FALSE;		//���S��Ԃɂ���
	DeathCount++;

	audio->Play("Bom");
	efect->Add(position - D3DXVECTOR3(32, 32, 0));	//�����G�t�F�N�g
	position.x -=9999;	//��΂ɂԂ���Ȃ��ꏊ�Ɉړ�������

	move.x = 0;
	move.y = 0;


	//�����ʒu
	position.x = 0;							//��ʂ̂P�ԍ��ɕ\��
	position.y = rand() % 618 + 150;	//�����_���ȏc�ʒu�ɕ\��
	action = rand() % 10;
	zannzou = rand() % 2;

	//�G�𐶑���Ԃɂ���
	isLive = TRUE;
}

HRESULT Enemy::Hit(UnitBase* pTarget)
{
	//�ړ����x
	if (typeid(*pTarget) == typeid(Player))
	{
		Player* player = (Player*)pTarget;

		

		if (action == 0 || action == 2 || action == 4 || action == 6 || action == 8)
		{
			//�G�̈ʒu���擾
			D3DXVECTOR3 playerPos = player->GetPos();
			D3DXVECTOR3 move = position - playerPos;
			D3DXVec3Normalize(&move, &move);
			move *= 5;
			position -= move * (1.00 + (DeathCount / 200));

			if (position.x >= 200)
			{
				position.y += 15;
			}
			if (position.x >= 400)
			{
				position.y -= 30;
			}
			if (position.x >= 600)
			{
				position.y += 15;
			}
			position -= move;
		}
		if (action == 1 || action == 3 || action == 5 || action == 7)
		{
			//�G�̈ʒu���擾
			D3DXVECTOR3 playerPos = player->GetPos();
			D3DXVECTOR3 move = position - playerPos;
			D3DXVec3Normalize(&move, &move);
			move *= 10;
			position -= move * (1.00 + (DeathCount / 200));

			if (position.x >= 200)
			{
				position.y += 15;
			}
			if (position.x >= 400)
			{
				position.y -= 30;
			}
			position -= move;
		}

		if (action == 9)
		{
			

			//�G�̈ʒu���擾
			D3DXVECTOR3 playerPos = player->GetPos();
			D3DXVECTOR3 move = position - playerPos;
			D3DXVec3Normalize(&move, &move);
			move *= 5;
			position -= move * (1.00 + (DeathCount / 100));

			if (zannzou == 1)
			{
				if (position.x >= 550)
				{
					//�����ʒu
					position.x = 0;							//��ʂ̂P�ԍ��ɕ\��
					position.y = rand() % 618 + 150;	//�����_���ȏc�ʒu�ɕ\��
					action = 1;

					//�G�𐶑���Ԃɂ���
					isLive = TRUE;
				}
			}
		}
	}
	return S_OK;
}