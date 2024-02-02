#pragma once
//#include <cstdio>
//#include <cstdlib>
#include "SDL.h"
#include "GameCommon.h"
#include INPUT
#include RENDER
#include "Player.h"

/// <summary>
/// <para>Game</para>
/// <para>�Q�[���̊Ǘ��N���X</para>
/// </summary>
class Game 
{
public:
	Game();
	// �Q�[��������������
	GameStatus Initialize();
	// �Q�[�����[�v
	GameStatus RunGame();
	// �Q�[�����I������
	void Shutdown();
	// �Q�[���r���[��n��
	GameView* GetGameView();

private:
	// �Q�[���r���[
	GameView* gameView;
	// ���͊Ǘ��}�l�[�W���[
	Input* input;
	// �v���C���[
	Player* player;
	// Number of ticks since start of game
	Uint32 mTicksCount;

	// �Q�[����`�悵�܂�
	bool DrowGameView();
	// �Q�[�����Đ����܂�
	bool PlayGame(float deltaTime);
	// �t���[���Ԋu���Ԃ��擾
	float DeltaTime();

};