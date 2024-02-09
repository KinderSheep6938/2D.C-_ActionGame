#pragma once
#include "GameCommon.h"
#include INPUT_H
#include RENDER_H
#include TRANSFORM_H
#include "Physic.h"
#include "ColliderManager.h"

#define SPEED 250

/// <summary>
/// <para>Player</para>
/// <para>�v���C���[���Ǘ����܂�</para>
/// </summary>
class Player : protected Transform
{
public:
	Player(Vector2* sPos, Vector2* sSize, GameView* render, ColliderManager* cManager);
	// ���W�ړ�
	void Move(Vector2* val, float deltaTime);
	// �\��
	bool View();
	// �ړ������؂�ւ�
	void ChangeDire();
	// Transform�擾
	Transform* GetCollider();

private:
	// �W�����v
	bool canJump;
	// �ړ�����
	int moveDire;
	// �؂�ւ�����
	bool canChange;

	// ��������
	Physic* physic;
	// �����_�����O�̃|�C���^
	GameView* gameRender;
	// �ՓˊǗ��}�l�[�W���[�̃|�C���^
	ColliderManager* coll;

};