#include "Transform.h"

// コンストラクタ
Transform::Transform()
{
	pos = VECTOR_ZERO;
	size = VECTOR_ZERO;
	topEdge = VECTOR_ZERO;
	width = 0;
	height = 0;
}

/// <summary>
/// <para>Initialize</para>
/// <para>オブジェクト情報を初期化します</para>
/// </summary>
/// <param name="sPos">初期位置</param>
/// <param name="sSize">初期サイズ</param>
void Transform::Initialize(Vector2* sPos, Vector2* sSize) {
	pos = *sPos;
	size = *sSize;
	CreateEdge();
}

/// <summary>
/// <para>Translate</para>
/// <para>オブジェクトを移動させます</para>
/// </summary>
/// <param name="val">移動量</param>
void Transform::Translate(Vector2* val) {
	// 入力値がない
	if (val->x == 0 && val->y == 0)
	{
		// 処理しない
		return;
	}

	// 移動
	pos.x += val->x;
	pos.y += val->y;

	// 頂点座標更新
	CreateEdge();
}

/// <summary>
/// <para>Update</para>
/// <para>オブジェクト情報を更新します</para>
/// </summary>
void Transform::Update() {
	// 頂点座標更新
	CreateEdge();
}

/// <summary>
/// <para>ExistInScreen</para>
/// <para>オブジェクトが画面内に存在するか確認します</para>
/// </summary>
/// <returns>画面内判定</returns>
bool Transform::ExistInScreen() {
	
	//上部の頂点座標が画面内にあるか
	if (topEdge.y < WIN_H) {
		return true;
	}
	return false;

}

/// <summary>
/// <para>GetTransform</para>
/// <para>Transform情報のポインタを取得します</para>
/// </summary>
/// <returns>ポインタ</returns>
Transform* Transform::GetTransform() {
	return this;
}

/// <summary>
/// <para>GetEdgeListPtr</para>
/// <para>頂点座標の配列先頭ポインタを取得します</para>
/// </summary>
/// <returns>配列の先頭ポインタ</returns>
Vector2* Transform::GetTopEdgePtr() {
	return &topEdge;
}

/// <summary>
/// <para>GetWidth</para>
/// <para>オブジェクトの横幅を取得します</para>
/// </summary>
/// <returns>横幅</returns>
float Transform::GetWidth() {
	return width;
}

/// <summary>
/// <para>GetHeight</para>
/// <para>オブジェクトの縦幅を取得します</para>
/// </summary>
/// <returns>縦幅</returns>
float Transform::GetHeight() {
	return height;
}

/// <summary>
/// <para>CreateEdge</para>
/// <para>設定された位置、大きさから頂点座標を算出します</para>
/// </summary>
void Transform::CreateEdge() {
	// オブジェクト幅取得
	width = size.x * OBJECT_SIZE;
	height = size.y * OBJECT_SIZE;
	
	// 頂点座標取得
	topEdge = *pos.Sub((width / HALF), (height / HALF));
}