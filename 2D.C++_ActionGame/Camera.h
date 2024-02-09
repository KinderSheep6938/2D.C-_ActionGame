#pragma once
#include "GameCommon.h"
#include "Player.h"
#include "Block.h"
#include "Map.h"

/// <summary>
/// <para>Camera</para>
/// <para>�}�b�v���Ǘ����܂�</para>
/// </summary>
class Camera
{
public:
	Camera(Player* pl,Block* bl);
	
	void Scroll(Vector2* val);

private:
	// �J�����ʒu
	Vector2 pos;
	// �v���C���[�|�C���^
	Player* playerPtr;
	// �u���b�N�z��|�C���^
	Block* blockListPtr;
};