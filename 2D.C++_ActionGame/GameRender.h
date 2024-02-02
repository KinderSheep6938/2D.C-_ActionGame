#pragma once
#include "SDL.h"
#include "GameCommon.h"


//�J���[�R�[�h
#define BLACK_C 0,0,0
#define RED_C 0xff,0,0
#define GREEN_C 0,0xff,0
#define BLUE_C 0,0,0xff
#define PURPLE_C 0xff,0,0xff
#define YELLOW_C 0xff,0xff,0
#define CYAN_C 0,0xff,0xff
#define WHITE_C 0xff,0xff,0xff 

/// <summary>
/// <para>GameView</para>
/// <para>�Q�[���̊Ǘ��N���X</para>
/// </summary>
class GameView 
{
public:
	GameView();
	// �Q�[���r���[��������
	GameStatus Initialize();
	// �Q�[���r���[���폜
	void Shutdown();

	// ��ʃN���A
	bool Clear();
	// ��ʍX�V
	void Update();
	// �`��F�ݒ�
	void SetDrowColor(int color);
	// �l�p�`��
	void DrowSquare(Vector2* pos, Vector2* size, float gameScale);

	// �Q�[���E�B���h�E���擾
	SDL_Window* GetWindow();
	// �`�惌���_�����O���擾
	SDL_Renderer* GetRenderer();

private:
	// SDL�����E�B���h�E
	SDL_Window* mWindow;
	// 2D�`��̂��߂̃����_�����O
	SDL_Renderer* mRenderer;
	// ���ݐݒ肳��Ă���`��F
	int colorId;

};