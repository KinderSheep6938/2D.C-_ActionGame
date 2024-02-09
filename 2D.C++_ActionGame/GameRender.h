#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "GameCommon.h"

//�t�H���g�p�X
#define FONT_PATH "PixelMplus12-Regular.ttf"

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
/// <para>�Q�[���r���[�̊Ǘ��N���X</para>
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
	bool Clear(float height);
	// ��ʍX�V
	void Update();
	// �`��F�ݒ�
	void SetDrowColor(int color);
	// �l�p�`��
	void DrowSquare(Vector2* topEdge, float width, float height);
	// �����\��
	void DrowText(int val);

	// �Q�[���E�B���h�E���擾
	SDL_Window* GetWindow();
	// �`�惌���_�����O���擾
	SDL_Renderer* GetRenderer();

private:
	// SDL�����E�B���h�E
	SDL_Window* mWindow;
	// 2D�`��̂��߂̃����_�����O
	SDL_Renderer* mRenderer;
	// �摜�p�T�[�t�F�X
	SDL_Surface* image;
	// �摜�o�͗p�e�N�X�`��
	SDL_Texture* imageTexture;
	// ���ݐݒ肳��Ă���`��F
	int colorId;

};