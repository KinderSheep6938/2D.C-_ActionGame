#pragma once
#include "GameCommon.h"
#include "Vector2.h"

// 重力
#define GRAVITY -9.81

// 最大・最低速度
#define MAX_VELOCITY 5
#define MIN_VELOCITY 1

// 摩擦力
#define FRICTION 12

/// <summary>
/// <para>Gravity</para>
/// <para>オブジェクトに重力を反映させます</para>
/// </summary>
class Physic
{
public:
	// コンストラクタ
	Physic(float mass);
	// 重力加速度を取得
	Vector2 GetGravity(float deltaTime);
	// 重力加速度を初期化
	void ResetGravityVelocity();
	// 移動速度を取得
	Vector2 GetVelocity(Vector2* input, float deltaTime);

private:
	// 重量
	float mass;
	// 重力加速度
	float gravityVelocity;
	// 移動速度
	float moveVelocity;
};