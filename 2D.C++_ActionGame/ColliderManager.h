#pragma once
#include "GameCommon.h"
#include TRANSFORM_H
#include "Block.h"
#include <vector>

using namespace std;

/// <summary>
/// <para>ColliderManager</para>
/// <para>全体的に衝突を管理します</para>
/// </summary>
class ColliderManager
{
public:
	ColliderManager(Block* listPtr,int length);

	// 衝突取得
	Vector2* GetCollisionByGame(Transform* check, Vector2* move);

	// 衝突判定登録
	void SetCollider(Transform* set);

private:

	// 管理領域の先頭ポインタ
	vector<Transform*> transforms;
	// めり込み防止
	Vector2 rest;

	// オブジェクトの頂点座標を取得
	void GetEdge(Transform* obj, Vector2* outListPtr);
	// オブジェクトに一番近い頂点座標を取得
	Vector2* GetNearEdgeByObj(Vector2* obj, Vector2* edgeListPtr);
	// 衝突検査
	bool CheckCollision(Transform* check, Vector2* pos);
	// めり込み防止の移動量を取得
	void CollisionRestVal(Transform* coll, Transform* check, Vector2* nearCheckEdge, Vector2* move);
};