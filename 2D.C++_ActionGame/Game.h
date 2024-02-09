#pragma once
//#include <cstdio>
//#include <cstdlib>
#include "SDL.h"
#include "GameCommon.h"
#include INPUT_H
#include RENDER_H
#include "Player.h"
#include "Map.h"
#include "ColliderManager.h"
#include "Camera.h"

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
	// �}�b�v
	Map* map;
	// �ՓˊǗ�
	ColliderManager* collManager;
	// �K����
	Camera* camera;

	// Number of ticks since start of game
	Uint32 mTicksCount;
	//�`��X�V����
	bool needRender;


	// �Q�[����`�悵�܂�
	bool DrowGameView();
	// �Q�[�����Đ����܂�
	bool PlayGame(float deltaTime);
	// �J�����Ȃǂɔ��f�����܂�
	bool Output();
	// �t���[���Ԋu���Ԃ��擾
	float DeltaTime();

};