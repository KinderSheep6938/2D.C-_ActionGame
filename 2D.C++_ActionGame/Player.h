#pragma once
#include "GameCommon.h"
#include INPUT
#include RENDER

/// <summary>
/// <para>Input</para>
/// <para>プレイヤー入力を管理します</para>
/// </summary>
class Player 
{
public:
	Player(GameView* render);
	// 座標移動
	void Move(Vector2* val,float deltaTime);
	// 表示
	bool View();

private:
	// 位置
	Vector2 pos;
	// サイズ
	Vector2 size;
	// レンダリング
	GameView* gameRender;

};