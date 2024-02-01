#pragma once
//#include <cstdio>
//#include <cstdlib>
#include "SDL.h"
#include "GameCommon.h"

//�E�B���h�E�ݒ�
#define WIN_NAME "C++ Action"
#define WIN_TOP_X 100
#define WIN_TOP_Y 50

/// <summary>
/// <para>Game</para>
/// <para>�Q�[���̊Ǘ��N���X</para>
/// </summary>
class Game {
public:
	Game();
	//�Q�[��������������
	GameStatus Initialize();
	//�Q�[�����[�v
	void RunGame();
	//�Q�[�����I������
	void Shutdown();

private:
	//SDL�����E�B���h�E
	SDL_Window* mWindow;
	//2D�`��̂��߂̃����_�����O
	SDL_Renderer* mRenderer;
	// Number of ticks since start of game
	Uint32 mTicksCount;
	//�Q�[���̑��s���x������
	bool mIsRunning;

};