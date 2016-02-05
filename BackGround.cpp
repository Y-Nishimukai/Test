/*===========================================================================================
�T�@���F�v���C���[��ʂ̔w�i�̊֐���`
�쐬���F10��26��
�X�V���F
����ҁFYu Nishimukai
=============================================================================================*/

//---------------�C���N���[�h-----------------------
#include "BackGround.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�R���X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
BackGround::BackGround()
{
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�f�X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
BackGround::~BackGround()
{
}

//�@�\�F�ǂݍ��ݏ���
//�����F�Ȃ�
//�ߒl�F���������s��
HRESULT BackGround::Load()
{
	//�w�i�摜�ǂݍ���
	if (FAILED(sprite.Load("pict\\background.bmp")))
	{
		return E_FAIL;		//���s��Ԃ�
	}

	if (FAILED(spriteB.Load("pict\\brock.jpg")))
	{
		return E_FAIL;		//���s��Ԃ�
	}

	return S_OK;			//������Ԃ�
}

//�@�\�F�`�揈��
//�����F�Ȃ�
//�ߒl�F���������s��
HRESULT BackGround::Render()
{
	//�\���̂��쐬
	SpriteData data;
	

	sprite.Draw(&data);	//�X�v���C�g�N���X�̕`�揈�����Ă�ŕύX�������̂𔽉f������

	SpriteData dataB;
	dataB.pos.x = 700;
	dataB.pos.y = 640;
	dataB.scale = D3DXVECTOR2(1.5f, 1.0f);

	spriteB.Draw(&dataB);


	return S_OK;	//������Ԃ�
}
