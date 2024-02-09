#include "ColliderManager.h"
#include <iostream>
#include <cmath>


#define MAXEDGE 4

// コンストラクタ
ColliderManager::ColliderManager(Block* listPtr, int length) 
{
	// vector配列
	transforms = vector<Transform*>();

	// 現在のTransformポインタ
	Transform* nowPtr = nullptr;

	// 渡された長さ分、検査を行う
	for (int i = 0;i < length;i++) {
		// ポインタ算出
		nowPtr = (listPtr + i)->GetCollider();
		// 格納検査
		SetCollider(nowPtr);
	}
	
	rest = VECTOR_ZERO;
}

/// <summary>
/// <para>GetCollisionByGame</para>
/// <para>衝突</para>
/// </summary>
/// <param name="target"></param>
Vector2* ColliderManager::GetCollisionByGame(Transform* check, Vector2* move) 
{
	// めり込み防止用初期化
	rest = VECTOR_ZERO;
	// 衝突判定用
	bool coll = false;
	// 頂点座標を保存するメモリを確保
	Vector2* checkEdges = new Vector2[MAXEDGE];
	Vector2* collEdges = new Vector2[MAXEDGE];
	// 頂点座標を取得
	GetEdge(check, checkEdges);

	// 衝突オブジェ
	Transform* collObj = nullptr;
	// 衝突頂点座標
	Vector2* nearEdge = nullptr;
	// 配列検査
	for (Transform* &target : transforms)
	{
		collObj = target;
		// 対象オブジェクトに一番近い頂点座標を取得
		nearEdge = GetNearEdgeByObj(&target->pos,checkEdges);
		// 衝突を検査
		if (CheckCollision(target, nearEdge)) {
			coll = true;
			break;
		}

		// 頂点座標を取得
		GetEdge(target, collEdges);
		// 対象オブジェクトに一番近い頂点座標を取得
		nearEdge = GetNearEdgeByObj(&check->pos, collEdges);
		// 衝突を検査
		if (CheckCollision(check, nearEdge)) {
			coll = true;
			break;
		}
	}

	//衝突した
	if (coll) {
		//めり込み量算出
		CollisionRestVal(collObj, check, nearEdge, move);
	}
	// メモリ解放
	delete[] checkEdges;
	delete[] collEdges;
	return &rest;
}

/// <summary>
/// <para>SetCollider</para>
/// <para>Colliderを管理用リストに格納します</para>
/// </summary>
/// <param name="set"></param>
void ColliderManager::SetCollider(Transform* set) 
{
	// 配列検査
	for (Transform* &target : transforms)
	{
		// すでに同じものが格納されている
		if (target == set) 
		{
			return;
		}
	}
	
	// 格納
	transforms.push_back(set);
}

/// <summary>
/// <para>CollisionRestVal</para>
/// <para>衝突めり込みを防止するための移動量を算出します</para>
/// </summary>
/// <param name="coll">衝突先のTransform</param>
/// <param name="check">めり込み制御側のTransform</param>
/// <param name="nearCheckEdge"></param>
/// <returns></returns>
void ColliderManager::CollisionRestVal(Transform* coll, Transform* check, Vector2* nearCheckEdge, Vector2* move) {
	// 返却用
	rest = check->pos;

	// 頂点座標を保存するメモリを確保
	Vector2* collEdges = new Vector2[MAXEDGE];
	// 衝突先の頂点座標を取得
	GetEdge(coll, collEdges);
	// 自身に近い衝突先頂点座標を取得
	Vector2* nearCollEdge = GetNearEdgeByObj(nearCheckEdge, collEdges);
	
	// めり込み防止用幅量
	float restDistanceVal = 0;
	// 移動量の正負判定用
	Vector2* restSign = nearCollEdge->Sub(&coll->pos);
	// めり込み防止後の補正座標
	float restVal = 0;

	// 自身の頂点座標の横軸の傾きが衝突先の傾きより小さい
	if (move->x == 0) {
		// 縦向きにめり込み防止を行う
		restDistanceVal = (coll->GetHeight() / HALF) + (check->GetHeight() / HALF);
		// オブジェクトに対して上で衝突した
		if (0 < restSign->y) {
			restDistanceVal = -restDistanceVal;
		}
		//移動量算出
		restVal = (coll->pos.y - restDistanceVal) - check->pos.y;
		rest = Vector2(0, restVal);
	}
	else {
		// 横向きにめり込み防止を行う
		restDistanceVal = (coll->GetWidth() / HALF) + (check->GetWidth() / HALF);
		// オブジェクトに対して右で衝突した
		if (0 < restSign->x) {
			restDistanceVal = -restDistanceVal;
		}
		//補正後の座標
		restVal = (coll->pos.x - restDistanceVal) - check->pos.x;
		rest = Vector2(restVal, 0);
	}
	//メモリ解放
	delete[] collEdges;

	return;
}

/// <summary>
/// <para>GetEdge</para>
/// <para>オブジェクトに対して頂点座標リストを取得します</para>
/// <para>リスト使用終了時、メモリ解放が必要</para>
/// </summary>
/// <param name="obj">オブジェクト</param>
/// <returns>頂点座標リストの先頭ポインタ</returns>
void ColliderManager::GetEdge(Transform* obj, Vector2* outListPtr) {

	// オブジェクトの各幅を保管
	float width = obj->GetWidth();
	float height = obj->GetHeight();
	// 各頂点座標を取得
	outListPtr[LEFTUP] = *obj->GetTopEdgePtr();
	outListPtr[RIGHTUP] = *obj->GetTopEdgePtr()->Add(width, 0);
	outListPtr[LEFTDOWN] = *obj->GetTopEdgePtr()->Add(0, height);
	outListPtr[RIGHTDOWN] = *obj->GetTopEdgePtr()->Add(width, height);

	return;
}

/// <summary>
/// <para>GetNearEdgeByObj</para>
/// <para>設定された原点に対して一番近い頂点座標のポインタを取得します</para>
/// </summary>
/// <param name="obj">設定された原点</param>
/// <param name="edgeListPtr">頂点座標リストの先頭ポインタ</param>
/// <returns>対象の頂点座標のポインタ</returns>
Vector2* ColliderManager::GetNearEdgeByObj(Vector2* origin, Vector2* edgeListPtr) {

	// 検査頂点座標ポインタ
	Vector2* checkPtr = nullptr;
	
	// 初期化として最初の頂点座標を格納する
	Vector2* nearPtr = edgeListPtr;
	float nearDis = origin->Distance(edgeListPtr);
	float checkDis = 0;

	// 残りの頂点座標を検査する
	for (int i = 1;i < MAXEDGE;i++) {
		// 調査ポインタ算出
		checkPtr = edgeListPtr + i;

		// 距離算出
		checkDis = origin->Distance(checkPtr);
		// 算出した距離のほうが短い
		if (checkDis < nearDis) {
			nearPtr = checkPtr;
			nearDis = checkDis;
		}
	}

	// 近い頂点座標ポインタを返却
	return nearPtr;
}

/// <summary>
/// <para>CheckCollision</para>
/// <para>渡された座標がオブジェクトに衝突しているか検査します</para>
/// </summary>
/// <param name="check">オブジェクト</param>
/// <param name="pos">検査座標</param>
/// <returns></returns>
bool ColliderManager::CheckCollision(Transform* check, Vector2* pos) 
{
	Vector2* top = check->GetTopEdgePtr();
	// 横軸判定
	float deepX = top->x + check->GetWidth();
	bool collX = (top->x < pos->x && pos->x < deepX);

	// 縦軸判定
	float deepY = top->y + check->GetHeight();
	bool collY = (top->y < pos->y && pos->y < deepY);

	// 衝突している
	if (collX && collY) {
		return true;
	}
	return false;
}