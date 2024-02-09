#include "Block.h"

/// <summary>
/// <para>Block</para>
/// <para>�R���X�g���N�^</para>
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
/// <para>�����蔻��Ɏg�p��������擾���܂�</para>
/// </summary>
/// <returns>Transform���</returns>
Transform* Block::GetCollider() {
	return GetTransform();
}

/// <summary>
/// <para>View</para>
/// <para>�u���b�N��\������</para>
/// </summary>
/// <returns>������</returns>
bool Block::View()
{
	//NULL�`�F�b�N
	if (gameRender == nullptr)
	{
		return false;
	}

	gameRender->DrowSquare(GetTopEdgePtr(), GetWidth(), GetHeight());
	return true;
}
