#pragma once
#include "GameCommon.h"

// ���_ID
#define LEFTUP 0
#define RIGHTUP 1
#define LEFTDOWN 2
#define RIGHTDOWN 3

/// <summary>
/// <para>Transform</para>
/// <para>�I�u�W�F�N�g�̏����Ǘ����܂�</para>
/// </summary>
class Transform
{
public:
	Transform();

	// �ʒu
	Vector2 pos;
	// �T�C�Y
	Vector2 size;

	// ��񏉊���
	void Initialize(Vector2* sPos, Vector2* sSize);
	// �I�u�W�F�N�g�ړ�
	void Translate(Vector2* val);
	// �I�u�W�F�N�g���X�V
	void Update();
	// ��ʓ��ɑ��݂��邩�m�F����
	bool ExistInScreen();

	// Transform�擾
	Transform* GetTransform();
	// ���_���W�̃|�C���^
	Vector2* GetTopEdgePtr();
	// �e���̎擾
	float GetWidth();
	float GetHeight();

private:
	// �E�B���h�E���_�ɋ߂����_���W
	Vector2 topEdge;
	// ����
	float width;
	// �c��
	float height;

	// ���_���W�v�Z
	void CreateEdge();

};