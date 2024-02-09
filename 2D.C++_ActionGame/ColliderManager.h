#pragma once
#include "GameCommon.h"
#include TRANSFORM_H
#include "Block.h"
#include <vector>

using namespace std;

/// <summary>
/// <para>ColliderManager</para>
/// <para>�S�̓I�ɏՓ˂��Ǘ����܂�</para>
/// </summary>
class ColliderManager
{
public:
	ColliderManager(Block* listPtr,int length);

	// �Փˎ擾
	Vector2* GetCollisionByGame(Transform* check, Vector2* move);

	// �Փ˔���o�^
	void SetCollider(Transform* set);

private:

	// �Ǘ��̈�̐擪�|�C���^
	vector<Transform*> transforms;
	// �߂荞�ݖh�~
	Vector2 rest;

	// �I�u�W�F�N�g�̒��_���W���擾
	void GetEdge(Transform* obj, Vector2* outListPtr);
	// �I�u�W�F�N�g�Ɉ�ԋ߂����_���W���擾
	Vector2* GetNearEdgeByObj(Vector2* obj, Vector2* edgeListPtr);
	// �Փˌ���
	bool CheckCollision(Transform* check, Vector2* pos);
	// �߂荞�ݖh�~�̈ړ��ʂ��擾
	void CollisionRestVal(Transform* coll, Transform* check, Vector2* nearCheckEdge, Vector2* move);
};