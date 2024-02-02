#include "SDL.h"
#include "Player.h"
#include "GameCommon.h"
#include "SDL_system.h"

#define START_POS_X 100
#define START_POS_Y 50

Player::Player(GameView* render)
{
	pos.x = START_POS_X;
	pos.y = START_POS_Y;
	size.x = PLAYER_SIZE;
	size.y = PLAYER_SIZE;
	gameRender = render;
}

/// <summary>
/// <para>View</para>
/// <para>�v���C���[��\������</para>
/// </summary>
/// <returns>������</returns>
bool Player::View()
{
	//NULL�`�F�b�N
	if (gameRender == nullptr) 
	{
		return false;
	}

	gameRender->SetDrowColor(RED);
	gameRender->DrowSquare(&pos, &size, PLAYER_SIZE);
	return true;
}

/// <summary>
/// <para>Move</para>
/// <para>�v���C���[���ړ������܂�</para>
/// </summary>
/// <param name="input">���͒l</param>
void Player::Move(Vector2* input, float deltaTime)
{
	
	// ���͒l���Ȃ�
	if (input->x == 0 && input->y == 0) 
	{
		// �������Ȃ�
		return;
	}

	// �ړ�
	pos.x += input->x * deltaTime;
	pos.y += input->y * deltaTime;
}