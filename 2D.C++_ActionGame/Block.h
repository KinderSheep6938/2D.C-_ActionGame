#pragma once
#include "GameCommon.h"
#include RENDER_H
#include TRANSFORM_H

/// <summary>
/// <para>Block</para>
/// <para>ブロックを管理します</para>
/// </summary>
class Block : protected Transform
{
public:
	Block();
	Block(Vector2* sPos, Vector2* sSize, GameView* render);
	// 表示
	bool View();
	// Transform取得
	Transform* GetCollider();

private:
	// レンダリング
	GameView* gameRender;
};