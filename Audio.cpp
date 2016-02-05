/*===========================================================================================
�T�@���F�Q�[���̉���炷�N���X�̊֐���`
�쐬���F10��26��
�X�V���F
����ҁFYu Nishimukai
=============================================================================================*/

//---------------�C���N���[�h-----------------------
#include "Audio.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�R���X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Audio::Audio()
{

}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�f�X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Audio::~Audio()
{
	//XACT�V���b�g�_�E��
	xactEngine->ShutDown();


	//�T�E���h�o���N�J��
	SAFE_DELETE_ARRAY(soundBankData);

	//�E�F�[�u�o���N�J��
	UnmapViewOfFile(mapWaveBank);

	//�G���W���J��
	SAFE_RELEASE(xactEngine);

	//COM���C�u�����J��
	CoUninitialize();
}

//�@�\�FXACT�G���W���̏���
//�����F�Ȃ�
//�ߒl�F���s��������
HRESULT Audio::InitEngine()
{
	//COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	//�G���W���쐬
	if (FAILED(XACT3CreateEngine(0, &xactEngine)))
	{
		MessageBox(0, "XACT�G���W���̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return E_FAIL;		//���s��Ԃ�
	}

	//�p�����[�^�ݒ�
	XACT_RUNTIME_PARAMETERS xactParam = { 0 };
	xactParam.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
	if (FAILED(xactEngine->Initialize(&xactParam)))
	{
		MessageBox(0, "XACT�G���W���̃p�����[�^�ݒ�Ɏ��s���܂���", "�G���[", MB_OK);
		return E_FAIL;		//���s��Ԃ�
	}
	return S_OK;	//������Ԃ�
}

//�@�\�Fxwb�t�@�C����ǂݍ���
//�����F�t�@�C����
//�ߒl�F���s��������
HRESULT Audio::LoadWaveBank(char* fileName)
{
	//�t�@�C�����J��
	HANDLE  hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	//�t�@�C���T�C�Y�𒲂ׂ�
	DWORD  fileSize = GetFileSize(hFile, &fileSize);

	//�}�b�s���O(�u���z�A�h���X��ԁv�Ƃ����Ƃ���Ƀf�[�^���R�s�[���Ȃ���΂Ȃ�Ȃ��B�i���������d�l�j)
	HANDLE hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, fileSize, NULL);
	mapWaveBank = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);

	//�E�F�[�u�o���N�쐬
	if (FAILED(xactEngine->CreateInMemoryWaveBank(mapWaveBank, fileSize, 0, 0, &waveBank)))
	{
		//���s�������Ƃ����b�Z�[�W�{�b�N�X�ŕ\��
		MessageBox(0, "�E�F�[�u�o���N�쐬�Ɏ��s���܂���", fileName, MB_OK);

		return E_FAIL;		//���s��Ԃ�
	}

	//�n���h����Еt����
	CloseHandle(hMapFile);
	CloseHandle(hFile);

	return S_OK;		//������Ԃ�
}

//�@�\�Fxsb�t�@�C���̓ǂݍ���
//�����F�t�@�C����
//�ߒl�F���s��������
HRESULT Audio::LoadSoundBank(char* fileName)
{
	//�t�@�C�����J��
	HANDLE  hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	//�t�@�C���T�C�Y�𒲂ׂ�
	DWORD fileSize = GetFileSize(hFile, &fileSize);

	//�f�[�^��S���ǂ�
	soundBankData = new BYTE[fileSize];
	DWORD  byteRead;
	ReadFile(hFile, soundBankData, fileSize, &byteRead, NULL);

	//�T�E���h�o���N�쐬
	if (FAILED(xactEngine->CreateSoundBank(soundBankData, fileSize, 0, 0, &soundBank)))
	{
		MessageBox(0, "�T�E���h�o���N�쐬�Ɏ��s���܂���", fileName, MB_OK);

		return E_FAIL;		//���s��Ԃ�
	}

	//�n���h����Еt����
	CloseHandle(hFile);

	return S_OK;		//������Ԃ�
}

//�@�\�F����炷�̂ɕK�v�Ȋ֐��̓ǂݍ���
//�����FwaveBankFileName�@xwb�t�@�C���̖��O
//�����FsoundBankFileName�@xsb�t�@�C���̖��O
//�ߒl�F���s��������
HRESULT Audio::Load(char* waveBankFileName, char* soundBankFileName)
{
	//XACT�G���W���̍쐬
	if (FAILED(InitEngine()))
	{
		return E_FAIL;	//���s��Ԃ�
	}

	//WaveBank�ǂݍ���
	if (FAILED(LoadWaveBank(waveBankFileName)))
	{
		return E_FAIL;	//���s��Ԃ�
	}

	//SoundBank�ǂݍ���
	if (FAILED(LoadSoundBank(soundBankFileName)))
	{
		return E_FAIL;	//���s��Ԃ�
	}

	return S_OK;		//������Ԃ�
}

//�@�\�F�����Đ�������
//�����FcueName�@�L���[��(�c�[���Ŏw�肵������)���O
//�ߒl�F���������s��
HRESULT Audio::Play(char* cueName)
{
	//�L���[�̔ԍ����擾
	XACTINDEX cueIndex = soundBank->GetCueIndex(cueName);

	//�Đ�
	if (FAILED(soundBank->Play(cueIndex, 0, 0, NULL)))
	{
		return E_FAIL;		//���s��Ԃ�
	}
	return S_OK;			//������Ԃ�
}

//�@�\�F�����~������
//�����F�L���[�̖��O
//�ߒl�F���������s��
HRESULT Audio::Stop(char* cueName)
{
	//�L���[�̔ԍ����擾
	XACTINDEX cueIndex = soundBank->GetCueIndex(cueName);

	//��~
	if (FAILED(soundBank->Stop(cueIndex, XACT_FLAG_SOUNDBANK_STOP_IMMEDIATE)))
	{
		return E_FAIL;		//���s��Ԃ�
	}
	return S_OK;			//������Ԃ�
}
