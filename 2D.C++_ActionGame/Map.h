#pragma once
#include "GameCommon.h"
#include RENDER_H
#include "Block.h"
#include <vector>

using namespace std;

// �u���b�N��
#define BLOCK_POOL 20

// �u���b�N�����ʒu�̃Y��
#define BLOCK_HEIGHT_DIF (OBJECT_SIZE * 3.5)
#define BLOCK_WIDTH_DIF OBJECT_SIZE

// �}�b�v�����̊�{���
#define START_WIDTH 10
#define MINUS_WIDTH 0.1
#define MIN_WIDTH 2.5
#define WIDTH_HOLE 2
#define MIN_FLOOR_FLATTYPE_WIDTH 1.5
#define MIN_FLOOR_HOLETYPE_WIDTH 5
#define WALL_SCALE Vector2(1,2);
#define NEXT_DIF (OBJECT_SIZE * 1)
#define FLOOR_TYPE_CYCLE 3

enum class FloorType : int 
{
	Flat,
	Hole
};

/// <summary>
/// <para>Map</para>
/// <para>�}�b�v���Ǘ����܂�</para>
/// </summary>
class Map
{
public:
	Map(GameView* render);
	
	// �\��
	bool View();
	// �����X�V
	void AddHeight(float val);
	// �����擾
	float GetHeight();

	// �u���b�N�̃I�u�W�F�N�g���̎擾
	Block* GetBlockListPtr();
	// �u���b�N�z��̒���
	int GetLength();

private:
	// �u���b�N�Ǘ��̔z��
	Block blocks[BLOCK_POOL];
	// �z��
	int length;
	// ��ԍ����t���A
	Transform* highestFloor;

	// ���݂̍���
	float nowHeight;
	// �I�u�W�F�N�g����
	float widthSize;
	// �i�s����
	int moveDire;
	// �t���A�����z��
	vector<FloorType> floor;
	// �t���A�����J�E���g
	int floorCnt;
	// �O��̃t���A�^�C�v�ۑ�
	FloorType nowFloor;

	// �����_�����O
	GameView* gameRender;

	// �t���A����
	void CreateFloor();
	// �t���A�^�C�v�擾
	FloorType GetFloorType();
	// �g�p�\�ȃu���b�N��ԋp
	Transform* GetUsableBlock();
};