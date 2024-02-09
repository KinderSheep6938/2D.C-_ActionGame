#include "Physic.h"
#include <cstdlib>

Physic::Physic(float setM) {
	mass = setM;
	gravityVelocity = 0;
	moveVelocity = 0;
}

/// <summary>
/// <para>GetGravity</para>
/// <para>���݂̏d�͉����x���擾���܂�</para>
/// </summary>
/// <param name="deltaTime">�t���[���o�ߎ���</param>
/// <returns>�d�͉����x</returns>
Vector2 Physic::GetGravity(float deltaTime) {
	//�d�͉����x�����Z
	gravityVelocity += mass * GRAVITY * deltaTime;
	return Vector2(0, -gravityVelocity);
}

/// <summary>
/// <para>ResetVelocity</para>
/// <para>�d�͉����x�����������܂�</para>
/// </summary>
void Physic::ResetGravityVelocity() {
	gravityVelocity = 0;
}

/// <summary>
/// <para>GetVelocity</para>
/// <para>���݂̈ړ����x���擾���܂�</para>
/// </summary>
/// <param name="input">����</param>
/// <param name="deltaTime">�t���[���o�ߎ���</param>
/// <returns>���ݑ��x</returns>
Vector2 Physic::GetVelocity(Vector2* input, float deltaTime) {

	// �c���͂�����
	if (input->y != 0) {
		// �d�͉����x�����Z
		gravityVelocity = input->y;
	}

	// �����͂̐������擾
	int sign = 1;
	if (moveVelocity < 0) {
		sign = -1;
	}

	// �����͂�����
	if (input->x != 0) {
		// ���x�����Z
		moveVelocity += input->x * deltaTime;
		// �ő呬�x�𒴂��Ă��邩
		if (MAX_VELOCITY <= std::abs(moveVelocity)) {
			// ���x�𐧌�
			moveVelocity = MAX_VELOCITY * sign;
		}
	}
	else {
		// ���C�͂𔽉f
		moveVelocity -= moveVelocity * FRICTION * deltaTime;
		// �Œᑬ�x�𒴂��Ă��Ȃ���
		if (std::abs(moveVelocity) <= MIN_VELOCITY) {
			// ���x��������
			moveVelocity = 0;
		}
	}

	return Vector2(moveVelocity, 0);
}