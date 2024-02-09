#include "Player.h"

/// <summary>
/// <para>Player</para>
/// <para>�R���X�g���N�^</para>
/// </summary>
Player::Player(Vector2* sPos, Vector2* sSize, GameView* render, ColliderManager* cManager)
{
	Initialize(sPos, sSize);
	canJump = false;
	moveDire = 1;
	canChange = true;
	physic = new Physic(300);
	gameRender = render;
	coll = cManager;
}

/// <summary>
/// <para>GetCollider</para>
/// <para>�Փ˔���Ɏg�p��������擾���܂�
/// </summary>
/// <returns>�I�u�W�F�N�g���</returns>
Transform* Player::GetCollider() {
	return GetTransform();
}

/// <summary>
/// <para>View</para>
/// <para>�v���C���[��\������</para>
/// </summary>
/// <returns>������</returns>
bool Player::View()
{
	//NULL�`�F�b�N
	if (gameRender == nullptr) 
	{
		return false;
	}

	gameRender->SetDrowColor(RED);
	gameRender->DrowSquare(GetTopEdgePtr(), GetWidth(), GetHeight());
	return true;
}

/// <summary>
/// <para>ChangeDire</para>
/// <para>�ړ�������؂�ւ��܂�</para>
/// </summary>
void Player::ChangeDire() {
	moveDire = -moveDire;
}

/// <summary>
/// <para>Move</para>
/// <para>�v���C���[���ړ������܂�</para>
/// </summary>
/// <param name="input">���͒l</param>
void Player::Move(Vector2* input, float deltaTime)
{
	//�W�����v�s�\�ɉ��ݒ�
	canJump = false;
	// �d��
	Vector2 gravityScale = physic->GetGravity(deltaTime);
	Translate(gravityScale.Multi(deltaTime));
	// �߂荞�ݗʎ擾
	Vector2* restVal = coll->GetCollisionByGame(GetCollider(), &gravityScale);
	// �߂荞�ݗʂ��ݒ肳��Ă���
	if (restVal->y != 0) {
		// �v���C���[�ړ�
		Translate(restVal);
		// �d�͉����x������
		physic->ResetGravityVelocity();

		// ���Ɍ��������x��
		if (0 < gravityScale.y) {
			// �W�����v�\��
			canJump = true;

		}
	}

	Vector2 val = *input->Add(SPEED * moveDire, 0);
	// �W�����v�s�\��
	if (!canJump) {
		canChange = true;
		val = Vector2(SPEED * moveDire,0);
	}

	// �v���C���[�ړ�
	Vector2 move = physic->GetVelocity(&val, deltaTime);
	Translate(&move);
	// �߂荞�ݗʎ擾
	restVal = coll->GetCollisionByGame(GetCollider(), &move);
	// �߂荞�ݗʂ��ݒ肳��Ă���
	if (restVal->x != 0) {
		// �v���C���[�ړ�
		Translate(restVal);
		if (canChange) {
			// �ړ������؂�ւ�
			ChangeDire();
			canChange = false;
		}

	}
}