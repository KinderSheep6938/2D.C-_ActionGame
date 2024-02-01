#pragma once
#include "SDL.h"
#include "GameCommon.h"

/// <summary>
/// <para>Input</para>
/// <para>プレイヤー入力を管理します</para>
/// </summary>
class Player {
public:
	Player();
	//座標移動
	void Move(Vector2 val);

private:
	//位置
	Vector2 pos;
	//サイズ
	Vector2 size;
	//2D描画のためのレンダリング
	SDL_Renderer* mRenderer;

};