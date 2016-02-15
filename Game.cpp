/*=======================================================================================================
�T�@���F�Q�[���S�̗̂������������
�쐬���F10��26��
�X�V���F
����ҁFYu Nishimukai
=======================================================================================================*/

//---------------�C���N���[�h-----------------------
#include "Game.h"
#include "TitleScene.h"
#include "TutorialScene.h"
#include "WaitingScene.h"
#include "PlayScene.h"
#include "ClearScene.h"

//----------------�O���[�o���ϐ�----------------
GAME_SCENE g_gameScene;				//���݂̃Q�[���V�[��
LPDIRECT3DDEVICE9 g_pDevice;		//Direct3D�f�o�C�X�I�u�W�F�N�g
Input*          g_pInput;			//���͏����I�u�W�F�N�g
LPD3DXFONT g_pFont = NULL;


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�R���X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Game::Game()
{
	//�e�V�[���I�u�W�F�N�g�̐���
	scene[SC_TITLE] = new TitleScene;		//�^�C�g���V�[��
	scene[SC_TUTORIAL] = new TutorialScene;
	scene[SC_WAITING] = new WaitingScene;
	scene[SC_PLAY] = new PlayScene;		//�v���C�V�[��
	scene[SC_END] = new ClearScene;

	//�ŏ��̓^�C�g���V�[��
	g_gameScene = SC_TITLE;
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�f�X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Game::~Game()
{
	for (int i = 0; i < SC_MAX; i++)
	{
		delete scene[i];
	}

	//DirectX�J��
	SAFE_RELEASE(g_pDevice);	//�f�o�C�X�I�u�W�F�N�g
	SAFE_RELEASE(pD3d);			//Direct3D�I�u�W�F�N�g
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// Direct3D������
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Game::InitD3d(HWND hWnd)
{
	// �uDirect3D�v�I�u�W�F�N�g�̍쐬
	if (NULL == (pD3d = Direct3DCreate9(D3D_SDK_VERSION)))		//Direct3D���쐬���Ď��s���ĂȂ�������
	{
		MessageBox(0, "Direct3D�̍쐬�Ɏ��s���܂���", "", MB_OK);		//���s���Ă����烁�b�Z�[�W�{�b�N�X�Ŏ��s��\��

		return E_FAIL;		//���s�������Ƃ�Ԃ�
	}


	// �uDIRECT3D�f�o�C�X�v�I�u�W�F�N�g�̍쐬(�\����)
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));								//������
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;			//�o�b�N�o�b�t�@�̃t�H�[�}�b�g
	d3dpp.BackBufferCount = 1;						//�p�ӂ���o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//�X���b�v
	d3dpp.Windowed = TRUE;					//�f�B�X�v���C�S�̂ɊG��\�����������Ƃ���FALSE
	d3dpp.EnableAutoDepthStencil = TRUE;					//Z�o�b�t�@(���s���j���g��(TURE)���g��Ȃ�(FALSE)��
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				//�o�b�t�@�̃t�H�[�}�b�g

	//�Q�[����ʂ̍쐬
	if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice)))				//���ɂ���Ă�Direct3D�̍쐬�Ɏ��s����\�������邽��if���ɂ���
	{
		//���s�����烁�b�Z�[�W�{�b�N�X�Œm�点��
		MessageBox(0, "HAL���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�", NULL, MB_OK);

		//�p�t�H�[�}���X�𗎂Ƃ��čēx�쐬
		if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice)))			//����ł����s����\��������
		{
			//���s��m�点��
			MessageBox(0, "DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���", NULL, MB_OK);
			return E_FAIL;			//���s��Ԃ�
		}
	}

	return S_OK;	//������Ԃ�

}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�ǂݍ��ݏ���
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Game::Load()
{
	//�S�ẴV�[���̓ǂݍ���
	for (int i = 0; i < SC_MAX; i++)
	{
		//�ǂ����Ŏ��s���Ă�����
		if (FAILED(scene[i]->Load()))
		{
			return E_FAIL;	//���s��Ԃ��iMain�֐��Ɂj
		}
	}
	return S_OK;
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�Փ˔���
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Game::Hit()
{
	//�ǂ����Ŏ��s���Ă�����
	if (FAILED(scene[g_gameScene]->Hit()))
	{
		return E_FAIL;	//���s���Ă�����
	}
	return S_OK;	//������ς���
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�X�V����
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Game::Update()
{
	//���͏����̍X�V�����i�L�[�̏�Ԃ𒲂ׂ�j
	g_pInput->Update();

	//�ǂ����Ŏ��s���Ă�����
	if (FAILED(scene[g_gameScene]->Update()))
	{
		return E_FAIL;	//���s��Ԃ�
	}
	return S_OK;	//������Ԃ�
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�`�揈��
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Game::Render()
{
	//��ʂ��N���A(XRGB�ŉ�ʂ̐F��@ZBUFFER��z�o�b�t�@���N���A�ɂ��Ă���j
	g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pDevice->BeginScene()))		//DirectX���Ƃ����Ŏ��s����Ƃ�������̂Ő������������肷��
	{

		//�Q�[����ʂ̕`��
		if (FAILED(scene[g_gameScene]->Render()))	//�ǂ����Ŏ��s���Ă�����
		{
			return E_FAIL;	//���s��Ԃ�
		}

		//�`��I��
		g_pDevice->EndScene();
		//BeginScene��EndScene��BeginPaint��EndPaint�̂悤�ȃC���[�W�ł悢
	}

	//�t���b�v
	//Direct3D�ł�2���̉�ʁi�t�����g�o�b�t�@�A�o�b�N�o�b�t�@�j��p�ӂ��ăo�b�N�o�b�t�@�̂ق��ɉ摜��`�悷��
	//�S�Ẳ摜��`�悵����A�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@���������邱����t���b�v�Ƃ���
	g_pDevice->Present(NULL, NULL, NULL, NULL);

	return S_OK;	//������Ԃ�
}

