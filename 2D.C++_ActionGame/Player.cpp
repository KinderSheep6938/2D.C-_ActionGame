#include "Player.h"

/// <summary>
/// <para>Player</para>
/// <para>コンストラクタ</para>
/// </summary>
Player::Player(Vector2* sPos, Vector2* sSize, GameView* render, ColliderManager* cManager)
{
	Initialize(sPos, sSize);
	canJump = false;
	moveDire = 1;
	canChange = true;
	physic = new Physic(300);
	gameRender = render;
	coll = cManager;
}

/// <summary>
/// <para>GetCollider</para>
/// <para>衝突判定に使用する情報を取得します
/// </summary>
/// <returns>オブジェクト情報</returns>
Transform* Player::GetCollider() {
	return GetTransform();
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
	gameRender->DrowSquare(GetTopEdgePtr(), GetWidth(), GetHeight());
	return true;
}

/// <summary>
/// <para>ChangeDire</para>
/// <para>移動方向を切り替えます</para>
/// </summary>
void Player::ChangeDire() {
	moveDire = -moveDire;
}

/// <summary>
/// <para>Move</para>
/// <para>プレイヤーを移動させます</para>
/// </summary>
/// <param name="input">入力値</param>
void Player::Move(Vector2* input, float deltaTime)
{
	//ジャンプ不可能に仮設定
	canJump = false;
	// 重力
	Vector2 gravityScale = physic->GetGravity(deltaTime);
	Translate(gravityScale.Multi(deltaTime));
	// めり込み量取得
	Vector2* restVal = coll->GetCollisionByGame(GetCollider(), &gravityScale);
	// めり込み量が設定されている
	if (restVal->y != 0) {
		// プレイヤー移動
		Translate(restVal);
		// 重力加速度初期化
		physic->ResetGravityVelocity();

		// 下に向かう速度か
		if (0 < gravityScale.y) {
			// ジャンプ可能に
			canJump = true;

		}
	}

	Vector2 val = *input->Add(SPEED * moveDire, 0);
	// ジャンプ不可能か
	if (!canJump) {
		canChange = true;
		val = Vector2(SPEED * moveDire,0);
	}

	// プレイヤー移動
	Vector2 move = physic->GetVelocity(&val, deltaTime);
	Translate(&move);
	// めり込み量取得
	restVal = coll->GetCollisionByGame(GetCollider(), &move);
	// めり込み量が設定されている
	if (restVal->x != 0) {
		// プレイヤー移動
		Translate(restVal);
		if (canChange) {
			// 移動方向切り替え
			ChangeDire();
			canChange = false;
		}

	}
}