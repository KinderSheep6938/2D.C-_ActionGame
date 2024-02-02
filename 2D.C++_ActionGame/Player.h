#pragma once
#include "GameCommon.h"
#include INPUT
#include RENDER

/// <summary>
/// <para>Input</para>
/// <para>�v���C���[���͂��Ǘ����܂�</para>
/// </summary>
class Player 
{
public:
	Player(GameView* render);
	// ���W�ړ�
	void Move(Vector2* val,float deltaTime);
	// �\��
	bool View();

private:
	// �ʒu
	Vector2 pos;
	// �T�C�Y
	Vector2 size;
	// �����_�����O
	GameView* gameRender;

};