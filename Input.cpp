/*===========================================================================================
�T�@���F�Q�[���̓��͏������s���֐���`
�쐬���F10��26��
�X�V���F
����ҁFYu Nishimukai
=============================================================================================*/

//---------------�C���N���[�h-----------------------
#include "Input.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�R���X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Input::Input()
{
	//keyState��������
	ZeroMemory(keyState, sizeof(keyState));


}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�f�X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Input::~Input()
{
	//�L�[�{�[�h�̃A�N�Z�X�������
	if (pKeyDevice)
	{
		pKeyDevice->Unacquire();
	}

	//DirectInput���
	SAFE_RELEASE(pKeyDevice);
	SAFE_RELEASE(pDinput);

}


//�@�\�FDirectInput�̏���
//�����F�E�B���h�E�n���h��
//�ߒl�F���������s
HRESULT Input::Init(HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̍쐬
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&pDinput, NULL)))
	{
		return E_FAIL;	//�쐬�Ɏ��s�����玸�s��m�点��
	}

	// �uDirectInput�f�o�C�X�v�I�u�W�F�N�g�̍쐬
	if (FAILED(pDinput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, NULL)))
	{
		return E_FAIL;	//���s��m�点��
	}

	// �f�o�C�X���L�[�{�[�h�ɐݒ�
	if (FAILED(pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������x���̐ݒ�(�ʂ̃E�B���h�E���J���Ă��Ă��Q�[���ɔ����ł���悤�ɂ��邩���Ȃ���)
	if (FAILED(pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return E_FAIL;
	}

	return S_OK;	//������m�点��
}

//�@�\�F�e���̓f�o�C�X�̏�Ԃ��擾
//�����F�Ȃ�
//�ߒl�F���������s��
HRESULT  Input::Update()
{
	//XInput�ŏ����擾����O�ɑO��̏�������K�v�����邽�߂��̏����̑O�ɏ����Ȃ��Ƃ����Ȃ�
	memcpy(&prevButtonState, &controllerState, sizeof(controllerState));	//�O��̃R���g���[���̏�������

	// �f�o�C�X�̃A�N�Z�X�����擾����
	HRESULT hr = pKeyDevice->Acquire();

	//�R���g���[���[�̏�Ԃ��擾
	for (int i = 0; i < 4; i++)
	{
		connect[i] = XInputGetState(i, &controllerState[i]);

	}

	//�A�N�Z�X�����擾�ł����@�������́@�A�N�Z�X�������������������ĂȂ������Ƃ�
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		memcpy(prevKeyState, keyState, sizeof(keyState));	//�O��̃L�[�̏�������

		//�S�ẴL�[�̏�Ԃ��擾
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);	//�L�[�̏�Ԃ��2�����ikeyState�̃A�h���X�j�ɓn���Ă���
		return S_OK;	//������m�点��
	}
	return E_FAIL;	//���s��m�点��
}

//�@�\�F�C�ӂ̃L�[��������Ă��邩�`�F�b�N
//�����F�C�ӂ̃L�[
//�ߒl�F�C�ӂ̃L�[��������Ă��邩���Ȃ���
BOOL Input::IsKeyPush(DWORD keyCode)
{
	//�C�ӂ̃L�[��������Ă�����
	if (keyState[keyCode] & 0x80)
	{
		return TRUE; //�����Ă���
	}
	return FALSE;      //�����ĂȂ�
}

//�@�\:�C�ӂ̃L�[��������Ă���u�Ԃ��`�F�b�N
//����:�C�ӂ̃L�[
//�ߒl�F�C�ӃL�[�������ꂽ�u�Ԃ�
BOOL Input::IsKeyTap(DWORD keyCode)
{
	//�O��C�ӂ̃L�[��������Ă�����
	if (!(prevKeyState[keyCode] & 0x80) && keyState[keyCode] & 0x80)
	{
		return TRUE;	//�����Ă���
	}

	return FALSE;	//������Ă��Ȃ�
}

//�@�\�F�C�ӂ̃L�[�������ꂽ���`�F�b�N
//�����F�C�ӂ̃L�[
//�ߒl�F�����ꂽ���ǂ���
BOOL Input::IsKeyRelease(DWORD keyCode)
{
	//�L�[�������ꂽ��
	if (prevKeyState[keyCode] & 0x80 && !(keyState[keyCode] & 0x80))
	{
		return TRUE;	//�����ꂽ
	}

	return FALSE;		//�����Ă���
}

//�@�\�F�R���g���[���̔C�ӂ̃{�^����������Ă��邩
//�����FbuttonCode �C�ӂ̃{�^��
//����:ID		�@ �R���g���[������P��(�����l��1P)
//�ߒl�F������Ă��邩�ǂ���
BOOL Input::IsPadButtonPush(DWORD buttonCode, int ID)
{
	//�ڑ�����Ă��Ȃ��Q�[���p�b�h����������Ȃɂ����Ȃ�
	if (connect[ID] == ERROR_DEVICE_NOT_CONNECTED)
	{
		return FALSE;
	}

	//�{�^����������Ă��邩
	if (controllerState[ID].Gamepad.wButtons & buttonCode)
	{
		return TRUE; //�����Ă�
	}
	return FALSE;   //�����ĂȂ�
}

//�@�\:�C�ӂ̃{�^����������Ă���u�Ԃ��`�F�b�N
//�����FbuttonCode �C�ӂ̃{�^��
//����:ID		�@ �R���g���[������P��(�����l��1P)
//�ߒl:�C�Ӄ{�^���������ꂽ�u�Ԃ�
BOOL Input::IsPadButtonTap(DWORD buttonCode, int ID)
{
	//�ڑ�����Ă��Ȃ��Q�[���p�b�h����������Ȃɂ����Ȃ�
	if (connect[ID] == ERROR_DEVICE_NOT_CONNECTED)
	{
		return FALSE;
	}

	//�O��C�ӂ̃L�[��������Ă�����
	if (!(prevButtonState[ID].Gamepad.wButtons & buttonCode) && controllerState[ID].Gamepad.wButtons & buttonCode)
	{
		return TRUE;	//�����Ă���
	}

	return FALSE;	//������Ă��Ȃ�
}

//�@�\:�C�ӂ̃{�^���������ꂽ���`�F�b�N
//�����FbuttonCode �C�ӂ̃{�^��
//����:ID		�@ �R���g���[������P��(�����l��1P)
//�ߒl:�C�Ӄ{�^���������ꂽ�u�Ԃ�
BOOL Input::IsPadButtonRelease(DWORD buttonCode, int ID)
{
	//�ڑ�����Ă��Ȃ��Q�[���p�b�h����������Ȃɂ����Ȃ�
	if (connect[ID] == ERROR_DEVICE_NOT_CONNECTED)
	{
		return FALSE;
	}

	//�O��C�ӂ̃L�[��������Ă��邩
	if (prevButtonState[ID].Gamepad.wButtons & buttonCode && !(controllerState[ID].Gamepad.wButtons & buttonCode))
	{
		return TRUE;	//������
	}

	return FALSE;	//�����Ă��Ȃ�
}

//�@�\�F�R���g���[���̍��X�e�B�b�N���E�̌X�����擾
//�����F�R���g���[������P��
//�ߒl�F���E�̌X��
float Input::GetPadLStickX(int ID)
{
	//�ڑ�����Ă��Ȃ��Q�[���p�b�h����������Ȃɂ����Ȃ�
	if (connect[ID] == ERROR_DEVICE_NOT_CONNECTED)
	{
		return 0.0f;
	}

	//�R���g���[���̍��E�̌X�����擾�isThumbLX�����X�e�B�b�N�̉��̌X���ɂȂ�j
	float value = controllerState[ID].Gamepad.sThumbLX;

	//�f�b�h�]�[��(�z�R���Ȃǂŉ������Ȃ��Ă��X�e�B�b�N��|���Ă���Ɣ��f����Ă��܂��̂�h��)
	if (value < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && value > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return 0.0f;	//0��Ԃ�
	}

	//�X����Ԃ�
	return value / 32767;	//���ʂɕԂ���-32768�`32767�̒l�ɂȂ�̂Ōv�Z���ʓ|�ɂȂ�̂ōő�l�Ŋ�����-1�`1�̒l�ɂ���
}

//�@�\�F�R���g���[���̍��X�e�B�b�N�㉺�̌X�����擾
//�����F�R���g���[������P��
//�ߒl�F�㉺�̌X��
float Input::GetPadLStickY(int ID)
{
	//�ڑ�����Ă��Ȃ��Q�[���p�b�h����������Ȃɂ����Ȃ�
	if (connect[ID] == ERROR_DEVICE_NOT_CONNECTED)
	{
		return  0.0f;
	}

	//�R���g���[���̏㉺�̌X�����擾�isThumbLY�����X�e�B�b�N�̏c�̌X���ɂȂ�j
	float value = controllerState[ID].Gamepad.sThumbLY;



	//�f�b�h�]�[��(�z�R���Ȃǂŉ������Ȃ��Ă��X�e�B�b�N��|���Ă���Ɣ��f����Ă��܂��̂�h��)
	if (value < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && value > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		return 0.0f;	//0��Ԃ�
	}

	//�X����Ԃ�
	return value / 32767;	//���ʂɕԂ���-32768�`32767�̒l�ɂȂ�̂Ōv�Z���ʓ|�ɂȂ�̂ōő�l�Ŋ�����-1�`1�̒l�ɂ���
}

//�@�\�F�R���g���[���̉E�X�e�B�b�N���E�̌X�����擾
//�����F�R���g���[������P��
//�ߒl�F���E�̌X��
float Input::GetPadRStickX(int ID)
{
	//�ڑ�����Ă��Ȃ��Q�[���p�b�h����������Ȃɂ����Ȃ�
	if (connect[ID] == ERROR_DEVICE_NOT_CONNECTED)
	{
		return 0.0f;
	}

	//�R���g���[���̍��E�̌X�����擾�i
	float value = controllerState[ID].Gamepad.sThumbRX;



	//�f�b�h�]�[��(�z�R���Ȃǂŉ������Ȃ��Ă��X�e�B�b�N��|���Ă���Ɣ��f����Ă��܂��̂�h��)
	if (value < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && value > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		return 0.0f;	//0��Ԃ�
	}

	//�X����Ԃ�
	return value / 32767;	//���ʂɕԂ���-32768�`32767�̒l�ɂȂ�̂Ōv�Z���ʓ|�ɂȂ�̂ōő�l�Ŋ�����-1�`1�̒l�ɂ���
}

//�@�\�F�R���g���[���̉E�X�e�B�b�N�㉺�̌X�����擾
//�����F�R���g���[������P��
//�ߒl�F�㉺�̌X��
float Input::GetPadRStickY(int ID)
{
	//�ڑ�����Ă��Ȃ��Q�[���p�b�h����������Ȃɂ����Ȃ�
	if (connect[ID] == ERROR_DEVICE_NOT_CONNECTED)
	{
		return 0.0f;
	}
	//�R���g���[���̏㉺�̌X�����擾�isThumbLY�����X�e�B�b�N�̏c�̌X���ɂȂ�j
	float value = controllerState[ID].Gamepad.sThumbRY;



	//�f�b�h�]�[��(�z�R���Ȃǂŉ������Ȃ��Ă��X�e�B�b�N��|���Ă���Ɣ��f����Ă��܂��̂�h��)
	if (value <  XINPUT_GAMEPAD_TRIGGER_THRESHOLD  && value > -XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		return 0.0f;	//0��Ԃ�
	}

	//�X����Ԃ�
	return value / 32767;	//���ʂɕԂ���-32768�`32767�̒l�ɂȂ�̂Ōv�Z���ʓ|�ɂȂ�̂ōő�l�Ŋ�����-1�`1�̒l�ɂ���
}

//�@�\�F���g���K�[�̉������݂��擾
//�����F�R���g���[������P��
//�ߒl�F���g���K�[�̉�������
float Input::GetPadLTrigger(int ID)
{
	//�ڑ�����Ă��Ȃ��Q�[���p�b�h����������Ȃɂ����Ȃ�
	if (connect[ID] == ERROR_DEVICE_NOT_CONNECTED)
	{
		return 0.0f;
	}

	//���g���K�[�̉������݂̋������擾
	float value = controllerState[ID].Gamepad.bLeftTrigger;

	//�f�b�h�]�[��(�z�R���Ȃǂŉ������Ȃ��Ă��X�e�B�b�N��|���Ă���Ɣ��f����Ă��܂��̂�h��)
	if (value < XINPUT_GAMEPAD_TRIGGER_THRESHOLD  && value > -XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		return 0.0f;	//0��Ԃ�
	}

	//�X����Ԃ�
	return value / 255;
}

//�@�\�F�E�g���K�[�̉������݂��擾
//�����F�R���g���[������P��
//�ߒl�F�E�g���K�[�̉�������
float Input::GetPadRTrigger(int ID)
{
	//�ڑ�����Ă��Ȃ��Q�[���p�b�h����������Ȃɂ����Ȃ�
	if (connect[ID] == ERROR_DEVICE_NOT_CONNECTED)
	{
		return 0.0f;
	}

	//���g���K�[�̉������݂̋������擾
	float value = controllerState[ID].Gamepad.bRightTrigger;

	//�f�b�h�]�[��(�z�R���Ȃǂŉ������Ȃ��Ă��X�e�B�b�N��|���Ă���Ɣ��f����Ă��܂��̂�h��)
	if (value < XINPUT_GAMEPAD_TRIGGER_THRESHOLD  && value > -XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		return 0.0f;	//0��Ԃ�
	}

	//�X����Ԃ�
	return value / 255;
}

//�@�\�F�Q�[���p�b�h��U��������
//�����F�Ȃ�
//�ߒl�F�Ȃ�
void Input::Vibration(float leftSpeed, float rightSpeed, int ID)
{
	//�ڑ�����Ă��Ȃ��Q�[���p�b�h����������Ȃɂ����Ȃ�
	if (connect[ID] == ERROR_DEVICE_NOT_CONNECTED)
	{
		return;
	}

	//�U��������̂ɕK�v�ȍ\���̂̏���
	XINPUT_VIBRATION vibration[4];							//�\���̍쐬
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));	//������

	//�U���̋���(�����ōő�l�������|���Ă���̂ň����ɂ�0.0�{����1�{�܂ł̐��l�ɂ���K�v������)
	vibration[ID].wLeftMotorSpeed = leftSpeed * 65535; // �����[�^�[
	vibration[ID].wRightMotorSpeed = rightSpeed * 65535; // �E���[�^�[

	//�U��������
	XInputSetState(ID, &vibration[ID]);
}


