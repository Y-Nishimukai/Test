/*===========================================================================================
�T�@���F�Q�[���̓��͏������s���N���X�w�b�_�[
�쐬���F10��26��
�X�V���F
����ҁFYu Nishimukai
=============================================================================================*/
#pragma once

#define DIRECTINPUT_VERSION 0x800 //DirectInput �̃o�[�W�����ݒ�

//---------------�C���N���[�h-----------------------
#include <dinput.h>
#include <XInput.h>	//�R���g���[���p�̃C���N���[�h

//���C�u����
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")	//�C���v�b�g�̃o�[�W�����͂W�ŏ\��(DirectX�Ɠ������炢�̃o�[�W���������邪)
#pragma comment(lib,"Xinput.lib")	//�R���g���[���p

//�}�N��
#define SAFE_RELEASE(p)        { if(p != NULL) { (p)->Release(); (p) = NULL; } }	//LP�^�ϐ��̉������

class Input
{
	LPDIRECTINPUT8        pDinput;				//DirectInput�I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8  pKeyDevice;			//�f�o�C�X�I�u�W�F�N�g�i�L�[�{�[�h�j
	XINPUT_STATE		  controllerState[4];     //�R���g���[���[�̏��(�����̃R���g���[�����g�������Ȃ�z��ɂ���)
	XINPUT_STATE		  prevButtonState[4];		//�O��̃R���g���[���{�^���̏��

	BYTE				  keyState[256];		//�e�L�[�̏��(�L�[�������ꂽ�����f����ꍇ��BYTE�^�ɂ���g�p)
	BYTE				  prevKeyState[256];	//�O��̃L�[�̏��

	BOOL connect[4];							//�R���g���[�����ڑ�����Ă��邩




public:
	Input();	//�R���X�g���N�^
	~Input();	//�f�X�g���N�^

	HRESULT Init(HWND hWnd);			//DirectInput�̏���

	HRESULT Update();					//�e���̓f�o�C�X�̏�Ԃ��擾
	BOOL  IsKeyPush(DWORD keyCode);		//�C�ӂ̃L�[��������Ă��邩�`�F�b�N
	BOOL  IsKeyTap(DWORD keyCode);		//�C�ӂ̃L�[�������ꂽ�u�Ԃ��`�F�b�N
	BOOL  IsKeyRelease(DWORD keyCode);	//�C�ӂ̃L�[�������ꂽ���`�F�b�N

	//ID�����������w�肳����̂��ʓ|�Ȃ̂ł��̂Ƃ��͈����ɒl�������邱�Ƃŏȗ��ł���(�f�t�H���g����)

	BOOL  IsPadButtonPush(DWORD buttonCode, int ID = 0);			//�R���g���[���[�̃{�^����������Ă��邩
	BOOL IsPadButtonTap(DWORD buttonCode, int ID = 0);			//�R���g���[���̃{�^���������ꂽ�u�Ԃ�
	BOOL IsPadButtonRelease(DWORD buttonCode, int ID = 0);			//�R���g���[���̃{�^���������ꂽ��

	float GetPadLStickX(int ID = 0);								//���X�e�B�b�N�̍��E�̌X��
	float GetPadLStickY(int ID = 0);								//���X�e�B�b�N�̏㉺�̌X��
	float GetPadRStickX(int ID = 0);								//�E�X�e�B�b�N�̍��E�̌X��
	float GetPadRStickY(int ID = 0);								//�E�X�e�B�b�N�̏㉺�̌X��
	float GetPadLTrigger(int ID = 0);								//���g���K�[�̉�������
	float GetPadRTrigger(int ID = 0);								//�E�g���K�[�̉�������

	void  Vibration(float leftSpeed, float rightSpeed, int ID = 0);     //�U���G�t�F�N�g
};

