#pragma once
#include "GameCommon.h"
#include "Player.h"
#include "Block.h"
#include "Map.h"

/// <summary>
/// <para>Camera</para>
/// <para>マップを管理します</para>
/// </summary>
class Camera
{
public:
	Camera(Player* pl,Block* bl);
	
	void Scroll(Vector2* val);

private:
	// カメラ位置
	Vector2 pos;
	// プレイヤーポインタ
	Player* playerPtr;
	// ブロック配列ポインタ
	Block* blockListPtr;
};