#include "GameCommon.h"
#include RENDER

/// <summary>
/// <para>GameView</para>
/// <para>�R���X�g���N�^</para>
/// </summary>
GameView::GameView()
{
	mWindow = nullptr;
	mRenderer = nullptr;
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
bool GameView::Clear() 
{
	//NULL�`�F�b�N
	if (!mRenderer) 
	{
		return false;
	}

	SetDrowColor(BLACK);
	SDL_RenderClear(mRenderer);
	/* ���̕`�� */
	SetDrowColor(BLUE);
	SDL_RenderDrawLine(mRenderer, 0, 0, WIN_W - 1, WIN_H - 1);

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
void GameView::DrowSquare(Vector2* pos, Vector2* size, float gameScale)
{
	// �l�p�`�̏c��
	float width = (size->x * gameScale);
	float height = (size->y * gameScale);
	// �E�B���h�E�̌��_�ɋ߂��_
	float shaX = pos->x - width / HALF;
	float shaY = pos->y - height / HALF;
	// �E�B���h�E�̌��_�ɉ����_
	float deepX = pos->x + width / HALF;
	float deepY = pos->y + height / HALF;

	// ��ʓ��ɕ␳

	SDL_RenderDrawLine(mRenderer, shaX, shaY, deepX, deepY);

	//�`��
	SDL_Rect rect = { shaX, shaY, width, height };
	SDL_RenderFillRect(mRenderer, &rect);

	//��ʍX�V
	SDL_RenderPresent(mRenderer);
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

