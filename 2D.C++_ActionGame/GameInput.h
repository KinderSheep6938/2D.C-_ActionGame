#pragma once
#include "GameCommon.h"

//�ړ���
#define BIG_JUMP 1100
#define SMALL_JUMP 650

/// <summary>
/// <para>Input</para>
/// <para>�v���C���[���͂��Ǘ����܂�</para>
/// </summary>
class Input 
{
public:
	Input();
	// �v���C���[���͎擾
	void SetInputByPlayer();
	// ���̓f�[�^�擾
	Vector2* GetInput();
	// �f�o�b�N�L�[�擾
	bool GetDebug();

private:
	// �ړ�����
	Vector2 inputVal;
	// �Ńo�b�N�L�[
	bool shutdown;

};