/*===========================================================================================
�T�@���F�v���W�F�N�g�S�̂ŕK�v�Ȃ��̂��܂Ƃ߂��t�@�C��
�쐬���F10��26��
�X�V���F
����ҁFYu Nishimukai
=============================================================================================*/
#pragma once

//---------------�C���N���[�h-----------------------
#include <windows.h>
#include <d3dx9.h>
#include "Input.h"


//----------���C�u�����t�@�C���̃��[�h--------------
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

//-------------------�萔�錾------------------
//�E�B���h�E�T�C�Y
#define WINDOW_WIDTH	1024		//�E�B���h�E�̕�
#define WINDOW_HEIGHT	768		//�E�B���h�E����
#define ENEMY_LIMIT		  1		//�G�̍ő吔
#define CHAR_SIZE		 32		//���@�ƓG�̃T�C�Y

//-------------------�}�N��----------------------
#define SAFE_DELETE(p) {delete(p);	(p) = NULL;}					//���I�ɍ�������m�����S�Ƀf���[�g����
#define SAFE_DELETE_ARRAY(p) {delete[] (p);  (p) = NULL;}			//�z��p
#define SAFE_RELEASE(p) {if(p != NULL){(p)->Release(); (p) = NULL;}}	//LP�^�p

//-------------------�O���[�o���ϐ�------------------
//�V�[��
enum GAME_SCENE
{
	SC_TITLE,	//�^�C�g���V�[��
	SC_TUTORIAL,
	SC_WAITING,
	SC_PLAY,	//�v���C�V�[��
	SC_END,	//�N���A�V�[��
	SC_MAX
};
extern GAME_SCENE	g_gameScene;		//���Ԃ�Game.cpp�Ő錾

//Direct3D�f�o�C�X�I�u�W�F�N�g
extern LPDIRECT3DDEVICE9 g_pDevice;

//���͏����I�u�W�F�N�g
extern Input* g_pInput;	//�N���X�����Ƃ��͊�{�I�Ƀ|�C���^�ɂ��������ǂ�