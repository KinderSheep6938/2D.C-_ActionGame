#include "Block.h"

/// <summary>
/// <para>Block</para>
/// <para>コンストラクタ</para>
/// </summary>
Block::Block() 
{
	pos = VECTOR_ZERO;
	size = VECTOR_ONE;
	gameRender = nullptr;
}
Block::Block(Vector2* sPos, Vector2* sSize, GameView* render)
{
	Initialize(sPos, sSize);
	gameRender = render;
}

/// <summary>
/// <para>GetCollider</para>
/// <para>当たり判定に使用する情報を取得します</para>
/// </summary>
/// <returns>Transform情報</returns>
Transform* Block::GetCollider() {
	return GetTransform();
}

/// <summary>
/// <para>View</para>
/// <para>ブロックを表示する</para>
/// </summary>
/// <returns>成功可否</returns>
bool Block::View()
{
	//NULLチェック
	if (gameRender == nullptr)
	{
		return false;
	}

	gameRender->DrowSquare(GetTopEdgePtr(), GetWidth(), GetHeight());
	return true;
}
