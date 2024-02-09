#pragma once
#include "GameCommon.h"

// 頂点ID
#define LEFTUP 0
#define RIGHTUP 1
#define LEFTDOWN 2
#define RIGHTDOWN 3

/// <summary>
/// <para>Transform</para>
/// <para>オブジェクトの情報を管理します</para>
/// </summary>
class Transform
{
public:
	Transform();

	// 位置
	Vector2 pos;
	// サイズ
	Vector2 size;

	// 情報初期化
	void Initialize(Vector2* sPos, Vector2* sSize);
	// オブジェクト移動
	void Translate(Vector2* val);
	// オブジェクト情報更新
	void Update();
	// 画面内に存在するか確認する
	bool ExistInScreen();

	// Transform取得
	Transform* GetTransform();
	// 頂点座標のポインタ
	Vector2* GetTopEdgePtr();
	// 各幅の取得
	float GetWidth();
	float GetHeight();

private:
	// ウィンドウ原点に近い頂点座標
	Vector2 topEdge;
	// 横幅
	float width;
	// 縦幅
	float height;

	// 頂点座標計算
	void CreateEdge();

};