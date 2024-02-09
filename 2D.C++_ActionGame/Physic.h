#pragma once
#include "GameCommon.h"
#include "Vector2.h"

// �d��
#define GRAVITY -9.81

// �ő�E�Œᑬ�x
#define MAX_VELOCITY 5
#define MIN_VELOCITY 1

// ���C��
#define FRICTION 12

/// <summary>
/// <para>Gravity</para>
/// <para>�I�u�W�F�N�g�ɏd�͂𔽉f�����܂�</para>
/// </summary>
class Physic
{
public:
	// �R���X�g���N�^
	Physic(float mass);
	// �d�͉����x���擾
	Vector2 GetGravity(float deltaTime);
	// �d�͉����x��������
	void ResetGravityVelocity();
	// �ړ����x���擾
	Vector2 GetVelocity(Vector2* input, float deltaTime);

private:
	// �d��
	float mass;
	// �d�͉����x
	float gravityVelocity;
	// �ړ����x
	float moveVelocity;
};