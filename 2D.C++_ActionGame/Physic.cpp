#include "Physic.h"
#include <cstdlib>

Physic::Physic(float setM) {
	mass = setM;
	gravityVelocity = 0;
	moveVelocity = 0;
}

/// <summary>
/// <para>GetGravity</para>
/// <para>現在の重力加速度を取得します</para>
/// </summary>
/// <param name="deltaTime">フレーム経過時間</param>
/// <returns>重力加速度</returns>
Vector2 Physic::GetGravity(float deltaTime) {
	//重力加速度を加算
	gravityVelocity += mass * GRAVITY * deltaTime;
	return Vector2(0, -gravityVelocity);
}

/// <summary>
/// <para>ResetVelocity</para>
/// <para>重力加速度を初期化します</para>
/// </summary>
void Physic::ResetGravityVelocity() {
	gravityVelocity = 0;
}

/// <summary>
/// <para>GetVelocity</para>
/// <para>現在の移動速度を取得します</para>
/// </summary>
/// <param name="input">入力</param>
/// <param name="deltaTime">フレーム経過時間</param>
/// <returns>現在速度</returns>
Vector2 Physic::GetVelocity(Vector2* input, float deltaTime) {

	// 縦入力がある
	if (input->y != 0) {
		// 重力加速度を加算
		gravityVelocity = input->y;
	}

	// 横入力の正負を取得
	int sign = 1;
	if (moveVelocity < 0) {
		sign = -1;
	}

	// 横入力がある
	if (input->x != 0) {
		// 速度を加算
		moveVelocity += input->x * deltaTime;
		// 最大速度を超えているか
		if (MAX_VELOCITY <= std::abs(moveVelocity)) {
			// 速度を制限
			moveVelocity = MAX_VELOCITY * sign;
		}
	}
	else {
		// 摩擦力を反映
		moveVelocity -= moveVelocity * FRICTION * deltaTime;
		// 最低速度を超えていないか
		if (std::abs(moveVelocity) <= MIN_VELOCITY) {
			// 速度を初期化
			moveVelocity = 0;
		}
	}

	return Vector2(moveVelocity, 0);
}