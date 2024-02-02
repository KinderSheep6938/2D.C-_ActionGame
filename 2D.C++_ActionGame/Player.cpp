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
/// <para>プレイヤーを表示する</para>
/// </summary>
/// <returns>成功可否</returns>
bool Player::View()
{
	//NULLチェック
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
/// <para>プレイヤーを移動させます</para>
/// </summary>
/// <param name="input">入力値</param>
void Player::Move(Vector2* input, float deltaTime)
{
	
	// 入力値がない
	if (input->x == 0 && input->y == 0) 
	{
		// 処理しない
		return;
	}

	// 移動
	pos.x += input->x * deltaTime;
	pos.y += input->y * deltaTime;
}