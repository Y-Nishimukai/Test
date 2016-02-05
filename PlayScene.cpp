/*===========================================================================================
�T�@���F�v���C�V�[������������
�쐬���F10��26��
�X�V���F
����ҁFYu Nishimukai
=============================================================================================*/

//---------------�C���N���[�h-----------------------
#include "PlayScene.h"
#include "Player.h"		//�v���C���[�N���X
#include "Enemy.h"		//�G�N���X
#include "BackGround.h"	//�w�i�N���X

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�R���X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
PlayScene::PlayScene()
{
	unit.push_back(new BackGround);

	//���j�b�g��ǉ�
	unit.push_back(new Player);		//�v���C���[�N���X��ǉ�

	unit.push_back(new Enemy);		//�G�N���X��ǉ�
}

HRESULT PlayScene::Update()
{

	unit.push_back(new Enemy);

	return S_OK;
}
