#pragma once
#include "GameCommon.h"
#include INPUT_H
#include RENDER_H
#include TRANSFORM_H
#include "Physic.h"
#include "ColliderManager.h"

#define SPEED 250

/// <summary>
/// <para>Player</para>
/// <para>プレイヤーを管理します</para>
/// </summary>
class Player : protected Transform
{
public:
	Player(Vector2* sPos, Vector2* sSize, GameView* render, ColliderManager* cManager);
	// 座標移動
	void Move(Vector2* val, float deltaTime);
	// 表示
	bool View();
	// 移動方向切り替え
	void ChangeDire();
	// Transform取得
	Transform* GetCollider();

private:
	// ジャンプ
	bool canJump;
	// 移動方向
	int moveDire;
	// 切り替え制御
	bool canChange;

	// 物理挙動
	Physic* physic;
	// レンダリングのポインタ
	GameView* gameRender;
	// 衝突管理マネージャーのポインタ
	ColliderManager* coll;

};