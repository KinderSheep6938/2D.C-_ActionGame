#include "GameCommon.h"
#include RENDER_H
#include <filesystem>
#include <iostream>

#define SKY_POS Vector2(0,0)
#define GROUND_POS Vector2(0, WIN_H_CENTOR + WIN_H_CENTOR / HALF)
#define SCROLL_SPEED 3

/// <summary>
/// <para>GameView</para>
/// <para>�R���X�g���N�^</para>
/// </summary>
GameView::GameView()
{

	mWindow = nullptr;
	mRenderer = nullptr;
	image = nullptr;
	imageTexture = nullptr;
	colorId = WHITE;
}

/// <summary>
/// <para>Initialize</para>
/// <para>�Q�[���r���[�����������܂�</para>
/// </summary>
/// <returns>������������</returns>
GameStatus GameView::Initialize() 
{
	// SDL������
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	// �������Ɏ��s����
	if (sdlResult != 0) {
		SDL_Log("SDL���������ł��܂��� : %s", SDL_GetError());
		return GameStatus::Stop;
	}

	// SDL�E�B���h�E���쐬
	mWindow = SDL_CreateWindow(
		WIN_NAME, // �E�B���h�E�̃^�C�g��
		WIN_TOP_X, // �E�B���h�E�������x���W
		WIN_TOP_Y, // �E�B���h�E�������y���W
		WIN_W, // �E�B���h�E�̕�(width)
		WIN_H, // �E�B���h�E�̍���(height)
		0 // �t���O(�ݒ肵�Ȃ�����0)
	);


	// �����Ɏ��s����
	if (!mWindow) {
		SDL_Log("�E�B���h�E�̍쐬�Ɏ��s���܂��� : %s", SDL_GetError());
		return GameStatus::Stop;
	}

	// SDL�����_���[���쐬
	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	return GameStatus::Play;
}

/// <summary>
/// <para>Shutdown</para>
/// <para>�Q�[���r���[�̏I�������܂�</para>
/// </summary>
void GameView::Shutdown() 
{
	if (mRenderer) SDL_DestroyRenderer(mRenderer);
	if (mWindow) SDL_DestroyWindow(mWindow);

	SDL_Quit();
}

/// <summary>
/// <para>GetWindow</para>
/// <para>�Q�[���E�B���h�E���擾���܂�</para>
/// </summary>
SDL_Window* GameView::GetWindow() 
{
	return mWindow;
}

/// <summary>
/// <para>GetRenderer</para>
/// <para>�����_�����O���擾���܂�</para>
/// </summary>
SDL_Renderer* GameView::GetRenderer()
{
	return mRenderer;
}

/// <summary>
/// <para>Clear</para>
/// <para>��ʂ�����̉�ʂɏ��������܂�</para>
/// </summary>
/// <returns>������</returns>
bool GameView::Clear(float height) 
{
	//NULL�`�F�b�N
	if (!mRenderer) 
	{
		return false;
	}

	SetDrowColor(CYAN);
	SDL_RenderClear(mRenderer);
	/* ���̕`�� */

	Vector2 drowPos = SKY_POS;
	SetDrowColor(BLUE);
	DrowSquare(&drowPos, WIN_W, (WIN_H_CENTOR / HALF) - height / SCROLL_SPEED / HALF);
	SetDrowColor(BLACK);
	DrowSquare(&drowPos, WIN_W, -height / SCROLL_SPEED / SCROLL_SPEED);
	drowPos = *GROUND_POS.Add(0, -height / SCROLL_SPEED);
	SetDrowColor(GREEN);
	DrowSquare(&drowPos, WIN_W, WIN_H);

	return true;
}

/// <summary>
/// <para>Update</para>
/// <para>��ʂ��X�V���܂�</para>
/// </summary>
void GameView::Update()
{
	SDL_RenderPresent(mRenderer);
}

/// <summary>
/// <para>SetDrowColor</para>
/// <para>�`��F��ݒ肵�܂�</para>
/// </summary>
/// <param name="color">�ݒ肷��F</param>
void GameView::SetDrowColor(int color)
{
	// �����`��F�̏ꍇ�͏������Ȃ�
	if (colorId == color) return;

	// �F���Ƃɐݒ�
	switch (color)
	{
	case WHITE:		// ��
		SDL_SetRenderDrawColor(mRenderer, WHITE_C , SDL_ALPHA_OPAQUE);
		break;

	case RED:		// ��
		SDL_SetRenderDrawColor(mRenderer, RED_C, SDL_ALPHA_OPAQUE);
		break;

	case GREEN:		// ��
		SDL_SetRenderDrawColor(mRenderer, GREEN_C, SDL_ALPHA_OPAQUE);
		break;

	case BLUE:		// ��
		SDL_SetRenderDrawColor(mRenderer, BLUE_C, SDL_ALPHA_OPAQUE);
		break;

	case PURPLE:	// ��
		SDL_SetRenderDrawColor(mRenderer, PURPLE_C, SDL_ALPHA_OPAQUE);
		break;

	case YELLOW:	// ��
		SDL_SetRenderDrawColor(mRenderer, YELLOW_C, SDL_ALPHA_OPAQUE);
		break;

	case CYAN:		// ��
		SDL_SetRenderDrawColor(mRenderer, CYAN_C, SDL_ALPHA_OPAQUE);
		break;

	case BLACK:		// ��
		SDL_SetRenderDrawColor(mRenderer, BLACK_C, SDL_ALPHA_OPAQUE);
		break;

	default:
		//��O�͔��ɐݒ�
		SDL_SetRenderDrawColor(mRenderer, WHITE_C, SDL_ALPHA_OPAQUE);
		break;
	}
	colorId = color;
}

/// <summary>
/// <para>SetDrowSquare</para>
/// <para>�P�F�̎l�p��`�悵�܂�</para>
/// </summary>
/// <param name="pos">���W</param>
/// <param name="size">�傫��</param>
void GameView::DrowSquare(Vector2* topEdge,float width,float height)
{
	// �`����ݒ�
	SDL_Rect rect = SDL_Rect();
	rect.x = topEdge->x;
	rect.y = topEdge->y;
	rect.w = width;
	rect.h = height;

	// �`��
	SDL_RenderFillRect(mRenderer, &rect);
}

void GameView::DrowText(int val) {

	
	// �摜�̓ǂݍ���
	
	return;
}

/// <summary>
/// <para>FloatPermission</para>
/// <para>���͒l���ŏ��ő�l���Ɏ��߂܂�</para>
/// </summary>
/// <param name="value">���͒l</param>
/// <param name="bottom">�ŏ��l</param>
/// <param name="top">�ő�l</param>
/// <returns>�␳���ꂽ���͒l</returns>
void FloatPermission(float* value, float* bottom, float* top)
{
	// �ŏ��l��菬����
	if (value < bottom)
	{
		value = bottom;
		return;
	}

	// �ő�l���傫��
	if (top < value)
	{
		value = top;
		return;
	}
}

