/*===========================================================================================
�T�@���F�X�v���C�g��������
�쐬���F10��26��
�X�V���F
����ҁFYu Nishimukai
=============================================================================================*/

//---------------�C���N���[�h-----------------------
#include "Sprite.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�R���X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Sprite::Sprite()
{

}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�f�X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Sprite::~Sprite()
{
	//�������
	SAFE_RELEASE(pTexture);
	SAFE_RELEASE(pSprite);
}

//-------------------------------------
//	�@�\�F�摜�̓ǂݍ��ݏ���
//	�����F�摜�t�@�C���̖��O
//	�ߒl�F���������s�������Ƃ�Ԃ�
//--------------------------------------
HRESULT Sprite::Load(char* fileName)
{
	//�u�X�v���C�g�I�u�W�F�N�g�̍쐬]
	if (FAILED(D3DXCreateSprite(g_pDevice, &pSprite)))
	{
		//���s�����烁�b�Z�[�W�{�b�N�X�ŕ\��
		MessageBox(0, "�X�v���C�g�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return E_FAIL;	//���s�������Ƃ�Ԃ�(�V�[���̃��j�b�g�ȂǂŎ��s���Ă���Ƃ�)
	}

	//�u�e�N�X�`���I�u�W�F�N�g�v�̍쐬
	if (FAILED(D3DXCreateTextureFromFileEx(g_pDevice, fileName, 0, 0, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, NULL, NULL, NULL, &pTexture)))		//��1������Direct�RD�f�o�C�X�A��2�����Ƀt�@�C������
	{																								//�w�肷��ƃe�N�X�`��������A
		//���s������ǂ̉摜���ǂݍ��߂Ȃ��������\��												//�Ō�̈����Ɏw�肵���ϐ��ɁA���������e�N�X�`�����͂���
		MessageBox(0, "�e�N�X�`���̍쐬�Ɏ��s���܂���", fileName, MB_OK);
		return E_FAIL;	//���s�������Ƃ�Ԃ�(�V�[���̃��j�b�g�ȂǂŎ��s���Ă���Ƃ�)
	}

	//�e�N�X�`���̃T�C�Y���擾
	D3DSURFACE_DESC d3dds;					//�e�N�X�`���̏��������\����
	pTexture->GetLevelDesc(0, &d3dds);		//�e�N�X�`���̏����擾
	texsize.x = (FLOAT)d3dds.Width;				//���̃T�C�Y�擾
	texsize.y = (FLOAT)d3dds.Height;				//�����̃T�C�Y�擾
	return S_OK;	//�����������Ƃ�Ԃ�
}

//------------------------------------
//	�@�\�F�摜�̕`��
//	�����F�Ȃ�
//	�ߒl�F�Ȃ�
//------------------------------------
void Sprite::Draw(SpriteData* data)
{
	//��_
	D3DXVECTOR3  center = data->center;
	center.z = 0;	//SpriteData�\���̂�center��D3DXVECTOR2�^�Ȃ̂�z�������݂��Ȃ��̂ł��̏�����ǉ����Ȃ���z���̒l���ςɂȂ�	

	//�T�C�Y���ȗ������ꍇ�͉摜�T�C�Y���g��
	if (data->size.x == -999) data->size.x = texsize.x;
	if (data->size.y == -999) data->size.y = texsize.y;

	//��_�������l�̂܂܂�������
	if (center.x == -999 && center.y == -999)
	{
		center.x = data->size.x / 2;	//�摜�̒��S�ɂ���
		center.y = data->size.y / 2;
	}

	//�g��s��
	D3DXMATRIX matScale;	//�g��s��p�ϐ��쐬


	//�g��s��쐬
	D3DXMatrixScaling(&matScale, data->scale.x, data->scale.y, 1);


	//��]�s��
	D3DXMATRIX matRotate;		//��]�s��p�ϐ��쐬
	//��]�s��쐬
	D3DXMatrixRotationZ(&matRotate, D3DXToRadian(data->angle));		//D3DXToRadian�Ŋp�x�̒P�ʂ����W�A���ɕϊ��ł���

	//�ړ��s��
	D3DXMATRIX matTrans;	//�ړ��p�s��ϐ��쐬
	//�ړ��s��쐬
	D3DXMatrixTranslation(&matTrans, data->pos.x + center.x  * data->scale.x, data->pos.y + center.y  * data->scale.y, 0);	//��_�Ɗg��k�����|����Ɗ�_��
	//���炵�����𒼂����Ƃ��ł���

	//��Ɋg��s�������Ă��邽�ߑ��̍s�������Ă����ʂ͎g���Ȃ�
	//���̂Ƃ��͍s����u�|���Z�v���邱�Ƃō����ł���
	D3DXMATRIX matWorld = matScale * matRotate * matTrans;		//�s��|���Z


	//�X�v���C�g�ɍs���K�p
	pSprite->SetTransform(&matWorld);

	//��_������Ɉړ�
	center.x += data->pos.x;
	center.y += data->pos.y;

	//�`��n��
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);		//ALPHABLEND�͘a�󂷂��ALPHA�͓����x,BLEND�͍�����
	//�܂蔼�����Ɍ�����悤�ɐF�������邱��
	//������������ƂŔ������̉摜���g�����Ƃ��ł���




	//�`��ʒu(z���͎g��Ȃ�)
	D3DXVECTOR3 position = data->pos;		//D3DXVECTOR3��POINT�֐��Ǝ��Ă���x��,y��,�ɉ�����z��������

	//�؂蔲���ʒu
	RECT cut = { data->cut.x, data->cut.y, data->cut.x + data->size.x, data->cut.y + data->size.y };		//����ƉE���̎w��



	//�`��(�����͍�����\��t����e�N�X�`��,�ؔ����͈�,��_,�\���ʒu,�F(�����x,��,��,��))	//�F�̕ύX�͉摜�̌��X�̐F�������g�����ɂȂ�
	pSprite->Draw(pTexture, &cut, &center, &position, D3DCOLOR_ARGB(data->color.a, data->color.r, data->color.g, data->color.b));

	//�`��I���
	pSprite->End();
}



