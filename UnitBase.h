/*===========================================================================================
�T�@���F�e�Q�[�����j�b�g�̐e�N���X
�쐬���F10��26��
�X�V���F
����ҁFYu Nishimukai
=============================================================================================*/
#pragma once

//---------------�C���N���[�h-----------------------
#include "Global.h"
#include <typeinfo.h>


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�e�Q�[�����j�b�g�̐e�N���X
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class UnitBase
{
protected:
	//���j�b�g�̈ʒu
	D3DXVECTOR3      position;

public:

	//�f�X�g���N�^
	virtual ~UnitBase() { };		//������virtual�ɂ��Ƃ����Ȃ��Ǝq�N���X�Ńf�X�g���N�^���Ă΂�Ȃ��Ȃ�

	//�ǂݍ��ݏ���
	virtual HRESULT Load();		//Direct3D��Direct3D�̏������o���Ă���łȂ��Ɖ摜�̓ǂݍ��݂��ł��Ȃ��B
	//���܂Œʂ肾��Scene�̃R���X�g���N�^�œǂ݂���ł��������ꂾ�Ə������ł��ĂȂ���Ԃœǂݍ��ނ̂ŃG���[�Ȃ�
	//�̂ŕʂɓǂݍ��ޗp�̊֐���p�ӂ���

	//�X�V����
	virtual HRESULT Update();

	//�Փ˔��菈��
	//�����FpTarget	���肷�鑊�胆�j�b�g
	virtual HRESULT Hit(UnitBase* pTarget);

	//�`�揈��
	//�����Fhdc	�f�o�C�X�R���e�L�X�g�n���h��
	virtual HRESULT Render();

	//���݂̈ʒu���擾
	//�ߒl�F���݂̈ʒu
	D3DXVECTOR3 GetPos()	{ return position; }
};

