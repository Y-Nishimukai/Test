/*===========================================================================================
�T�@���F�N���A�N���X�̊֐���`
�쐬���F10��26��
�X�V���F
����ҁFYu Nishimukai
=============================================================================================*/

//---------------�C���N���[�h-----------------------
#include "Clear.h"
#include "Player.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�R���X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Clear::Clear()
{
	position.x = 0;
	position.y = -192;

}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�f�X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Clear::~Clear()
{
}

//�@�\�F�ǂݍ��ݏ���
//�����F�Ȃ�
//�ߒl�G���������s��
HRESULT Clear::Load()
{
	//�N���A�摜�ǂݍ���
	if (FAILED(sprite.Load("pict\\background.bmp")))
	{
		return E_FAIL;	//���s��Ԃ�
	}

	if (FAILED(spriteG.Load("pict\\GAMEOVER.png")))
	{
		return E_FAIL;	//���s��Ԃ�
	}

	if (FAILED(spriteM.Load("pict\\model.png")))
	{
		return E_FAIL;	//���s��Ԃ�
	}

	return S_OK;		//������Ԃ�
}

//�@�\�F�X�V����
//�����F�Ȃ�
//�ߒl�F���������s��
HRESULT Clear::Update()
{
	////�X�y�[�X�L�[�������ꂽ��^�C�g���V�[����
	//if (g_pInput->IsKeyTap(DIK_SPACE))
	//{
	//	g_gameScene = SC_TITLE;
	//}
	if (position.y <= 200)
	{
		position.y++;
	}

	return S_OK;		//������Ԃ�
}

//�@�\�F�`�揈��
//�����F�Ȃ�
//�ߒl�F���������s��
HRESULT Clear::Render()
{
	//�\���̂��쐬
	SpriteData data;

	sprite.Draw(&data);	//�X�v���C�g�N���X�̕`�揈�����Ă�ŕύX�������̂𔽉f������

	SpriteData dataG;
	dataG.pos.y = position.y;

	spriteG.Draw(&dataG);

	SpriteData dataM;
	dataM.pos.y = 645;
	spriteM.Draw(&dataM);
	

	return S_OK;	//������Ԃ�

}