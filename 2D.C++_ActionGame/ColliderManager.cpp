#include "ColliderManager.h"
#include <iostream>
#include <cmath>


#define MAXEDGE 4

// �R���X�g���N�^
ColliderManager::ColliderManager(Block* listPtr, int length) 
{
	// vector�z��
	transforms = vector<Transform*>();

	// ���݂�Transform�|�C���^
	Transform* nowPtr = nullptr;

	// �n���ꂽ�������A�������s��
	for (int i = 0;i < length;i++) {
		// �|�C���^�Z�o
		nowPtr = (listPtr + i)->GetCollider();
		// �i�[����
		SetCollider(nowPtr);
	}
	
	rest = VECTOR_ZERO;
}

/// <summary>
/// <para>GetCollisionByGame</para>
/// <para>�Փ�</para>
/// </summary>
/// <param name="target"></param>
Vector2* ColliderManager::GetCollisionByGame(Transform* check, Vector2* move) 
{
	// �߂荞�ݖh�~�p������
	rest = VECTOR_ZERO;
	// �Փ˔���p
	bool coll = false;
	// ���_���W��ۑ����郁�������m��
	Vector2* checkEdges = new Vector2[MAXEDGE];
	Vector2* collEdges = new Vector2[MAXEDGE];
	// ���_���W���擾
	GetEdge(check, checkEdges);

	// �Փ˃I�u�W�F
	Transform* collObj = nullptr;
	// �Փ˒��_���W
	Vector2* nearEdge = nullptr;
	// �z�񌟍�
	for (Transform* &target : transforms)
	{
		collObj = target;
		// �ΏۃI�u�W�F�N�g�Ɉ�ԋ߂����_���W���擾
		nearEdge = GetNearEdgeByObj(&target->pos,checkEdges);
		// �Փ˂�����
		if (CheckCollision(target, nearEdge)) {
			coll = true;
			break;
		}

		// ���_���W���擾
		GetEdge(target, collEdges);
		// �ΏۃI�u�W�F�N�g�Ɉ�ԋ߂����_���W���擾
		nearEdge = GetNearEdgeByObj(&check->pos, collEdges);
		// �Փ˂�����
		if (CheckCollision(check, nearEdge)) {
			coll = true;
			break;
		}
	}

	//�Փ˂���
	if (coll) {
		//�߂荞�ݗʎZ�o
		CollisionRestVal(collObj, check, nearEdge, move);
	}
	// ���������
	delete[] checkEdges;
	delete[] collEdges;
	return &rest;
}

/// <summary>
/// <para>SetCollider</para>
/// <para>Collider���Ǘ��p���X�g�Ɋi�[���܂�</para>
/// </summary>
/// <param name="set"></param>
void ColliderManager::SetCollider(Transform* set) 
{
	// �z�񌟍�
	for (Transform* &target : transforms)
	{
		// ���łɓ������̂��i�[����Ă���
		if (target == set) 
		{
			return;
		}
	}
	
	// �i�[
	transforms.push_back(set);
}

/// <summary>
/// <para>CollisionRestVal</para>
/// <para>�Փ˂߂荞�݂�h�~���邽�߂̈ړ��ʂ��Z�o���܂�</para>
/// </summary>
/// <param name="coll">�Փː��Transform</param>
/// <param name="check">�߂荞�ݐ��䑤��Transform</param>
/// <param name="nearCheckEdge"></param>
/// <returns></returns>
void ColliderManager::CollisionRestVal(Transform* coll, Transform* check, Vector2* nearCheckEdge, Vector2* move) {
	// �ԋp�p
	rest = check->pos;

	// ���_���W��ۑ����郁�������m��
	Vector2* collEdges = new Vector2[MAXEDGE];
	// �Փː�̒��_���W���擾
	GetEdge(coll, collEdges);
	// ���g�ɋ߂��Փː撸�_���W���擾
	Vector2* nearCollEdge = GetNearEdgeByObj(nearCheckEdge, collEdges);
	
	// �߂荞�ݖh�~�p����
	float restDistanceVal = 0;
	// �ړ��ʂ̐�������p
	Vector2* restSign = nearCollEdge->Sub(&coll->pos);
	// �߂荞�ݖh�~��̕␳���W
	float restVal = 0;

	// ���g�̒��_���W�̉����̌X�����Փː�̌X����菬����
	if (move->x == 0) {
		// �c�����ɂ߂荞�ݖh�~���s��
		restDistanceVal = (coll->GetHeight() / HALF) + (check->GetHeight() / HALF);
		// �I�u�W�F�N�g�ɑ΂��ď�ŏՓ˂���
		if (0 < restSign->y) {
			restDistanceVal = -restDistanceVal;
		}
		//�ړ��ʎZ�o
		restVal = (coll->pos.y - restDistanceVal) - check->pos.y;
		rest = Vector2(0, restVal);
	}
	else {
		// �������ɂ߂荞�ݖh�~���s��
		restDistanceVal = (coll->GetWidth() / HALF) + (check->GetWidth() / HALF);
		// �I�u�W�F�N�g�ɑ΂��ĉE�ŏՓ˂���
		if (0 < restSign->x) {
			restDistanceVal = -restDistanceVal;
		}
		//�␳��̍��W
		restVal = (coll->pos.x - restDistanceVal) - check->pos.x;
		rest = Vector2(restVal, 0);
	}
	//���������
	delete[] collEdges;

	return;
}

/// <summary>
/// <para>GetEdge</para>
/// <para>�I�u�W�F�N�g�ɑ΂��Ē��_���W���X�g���擾���܂�</para>
/// <para>���X�g�g�p�I�����A������������K�v</para>
/// </summary>
/// <param name="obj">�I�u�W�F�N�g</param>
/// <returns>���_���W���X�g�̐擪�|�C���^</returns>
void ColliderManager::GetEdge(Transform* obj, Vector2* outListPtr) {

	// �I�u�W�F�N�g�̊e����ۊ�
	float width = obj->GetWidth();
	float height = obj->GetHeight();
	// �e���_���W���擾
	outListPtr[LEFTUP] = *obj->GetTopEdgePtr();
	outListPtr[RIGHTUP] = *obj->GetTopEdgePtr()->Add(width, 0);
	outListPtr[LEFTDOWN] = *obj->GetTopEdgePtr()->Add(0, height);
	outListPtr[RIGHTDOWN] = *obj->GetTopEdgePtr()->Add(width, height);

	return;
}

/// <summary>
/// <para>GetNearEdgeByObj</para>
/// <para>�ݒ肳�ꂽ���_�ɑ΂��Ĉ�ԋ߂����_���W�̃|�C���^���擾���܂�</para>
/// </summary>
/// <param name="obj">�ݒ肳�ꂽ���_</param>
/// <param name="edgeListPtr">���_���W���X�g�̐擪�|�C���^</param>
/// <returns>�Ώۂ̒��_���W�̃|�C���^</returns>
Vector2* ColliderManager::GetNearEdgeByObj(Vector2* origin, Vector2* edgeListPtr) {

	// �������_���W�|�C���^
	Vector2* checkPtr = nullptr;
	
	// �������Ƃ��čŏ��̒��_���W���i�[����
	Vector2* nearPtr = edgeListPtr;
	float nearDis = origin->Distance(edgeListPtr);
	float checkDis = 0;

	// �c��̒��_���W����������
	for (int i = 1;i < MAXEDGE;i++) {
		// �����|�C���^�Z�o
		checkPtr = edgeListPtr + i;

		// �����Z�o
		checkDis = origin->Distance(checkPtr);
		// �Z�o���������̂ق����Z��
		if (checkDis < nearDis) {
			nearPtr = checkPtr;
			nearDis = checkDis;
		}
	}

	// �߂����_���W�|�C���^��ԋp
	return nearPtr;
}

/// <summary>
/// <para>CheckCollision</para>
/// <para>�n���ꂽ���W���I�u�W�F�N�g�ɏՓ˂��Ă��邩�������܂�</para>
/// </summary>
/// <param name="check">�I�u�W�F�N�g</param>
/// <param name="pos">�������W</param>
/// <returns></returns>
bool ColliderManager::CheckCollision(Transform* check, Vector2* pos) 
{
	Vector2* top = check->GetTopEdgePtr();
	// ��������
	float deepX = top->x + check->GetWidth();
	bool collX = (top->x < pos->x && pos->x < deepX);

	// �c������
	float deepY = top->y + check->GetHeight();
	bool collY = (top->y < pos->y && pos->y < deepY);

	// �Փ˂��Ă���
	if (collX && collY) {
		return true;
	}
	return false;
}