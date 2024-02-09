#pragma once
#include "GameCommon.h"
#include RENDER_H
#include TRANSFORM_H

/// <summary>
/// <para>Block</para>
/// <para>�u���b�N���Ǘ����܂�</para>
/// </summary>
class Block : protected Transform
{
public:
	Block();
	Block(Vector2* sPos, Vector2* sSize, GameView* render);
	// �\��
	bool View();
	// Transform�擾
	Transform* GetCollider();

private:
	// �����_�����O
	GameView* gameRender;
};