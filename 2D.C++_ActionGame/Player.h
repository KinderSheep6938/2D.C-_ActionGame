#pragma once
#include "SDL.h"
#include "GameCommon.h"

/// <summary>
/// <para>Input</para>
/// <para>�v���C���[���͂��Ǘ����܂�</para>
/// </summary>
class Player {
public:
	Player();
	//���W�ړ�
	void Move(Vector2 val);

private:
	//�ʒu
	Vector2 pos;
	//�T�C�Y
	Vector2 size;
	//2D�`��̂��߂̃����_�����O
	SDL_Renderer* mRenderer;

};