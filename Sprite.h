/*===========================================================================================
�T�@���F2D�摜(�X�v���C�g)�������N���X�w�b�_�[
�쐬���F10��26��
�X�V���F
����ҁFYu Nishimukai
=============================================================================================*/
#pragma once

//---------------�C���N���[�h-----------------------
#include "Global.h"

//�摜�̕\���Ɏg���f�[�^
struct SpriteData
{
	D3DXVECTOR3 pos;      //�ʒu
	D3DXVECTOR2 size;     //�T�C�Y
	D3DXVECTOR2 cut;      //�؂蔲���ʒu
	D3DXVECTOR2 center;   //��_
	D3DXVECTOR2 scale;	  //�g�嗦	
	float		angle;		//�p�x

	//�F
	struct
	{
		int a, r, g, b;
	}color;

	//�R���X�g���N�^(�����200�~200�̃T�C�Y�ŕ\��)
	//VisualStadio��C++���ƍ\���̂ŃR���X�g���N�^���ł��邪
	//java���Ƃ��������\���̂����݂��Ȃ��̂�
	//�݊������~���������肷��Ƃ��͂��������Ȃ��ŃN���X�������ق����ǂ�
	SpriteData()
	{
		pos = D3DXVECTOR3(0, 0, 0);			//�`��ʒu
		size = D3DXVECTOR2(-999, -999);		//�T�C�Y(�ȗ��������ꍇ��-999�Ŏw�肷��)
		cut = D3DXVECTOR2(0, 0);			//�ؔ����ʒu
		center = D3DXVECTOR2(-999, -999);			//��_
		color = { 255, 255, 255, 255 };		//�����x�ƐF
		scale = D3DXVECTOR2(1, 1);			//�g�嗦
		angle = 0;							//�p�x
	}
};

class Sprite
{
	//�X�v���C�g�I�u�W�F�N�g
	LPD3DXSPRITE pSprite;

	//�e�N�X�`���I�u�W�F�N�g
	LPDIRECT3DTEXTURE9 pTexture;

	//�e�N�X�`���̃T�C�Y
	D3DXVECTOR2 texsize;
public:
	Sprite();		//�R���X�g���N�^
	~Sprite();		//�f�X�g���N�^

	//�ǂݍ��ݏ���
	HRESULT Load(char* fileName);

	//�`�揈��
	void Draw(SpriteData* data);

	D3DXVECTOR2 GetSize(){ return texsize; }
};


