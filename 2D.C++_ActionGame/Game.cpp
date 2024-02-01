#include "Game.h"

/// <summary>
/// <para>Game</para>
/// <para>�R���X�g���N�^</para>
/// </summary>
Game::Game()
{
	mWindow = nullptr;
	mRenderer = nullptr;
	mTicksCount = 0;
	mIsRunning = true;
}

/// <summary>
/// <para>Initialize</para>
/// <para>�Q�[���̏���������</para>
/// </summary>
/// <returns>������������</returns>
GameStatus Game::Initialize() {
	// SDL������
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	// �������Ɏ��s����
	if (sdlResult != 0) {
		SDL_Log("SDL���������ł��܂��� : %s", SDL_GetError());
		return Stop;
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
		return Stop;
	}

	// SDL�����_���[���쐬
	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	return Play;
}

/// <summary>
/// <para>RunGame</para>
/// <para>�Q�[���̃v���C����</para>
/// </summary>
void Game::RunGame() {
	SDL_SetRenderDrawColor(mRenderer, 0xdf, 0xff, 0xdf, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(mRenderer);
	/* ���̕`�� */
	SDL_SetRenderDrawColor(mRenderer, 0xff, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(mRenderer, 0, 0, 319, 239);
	SDL_RenderPresent(mRenderer);
}

/// <summary>
/// <para>Shutdown</para>
/// <para>�Q�[���̏I������</para>
/// </summary>
void Game::Shutdown() {

	if (mRenderer) SDL_DestroyRenderer(mRenderer);
	if (mWindow) SDL_DestroyWindow(mWindow);

	SDL_Quit();
}
