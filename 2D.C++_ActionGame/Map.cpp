#include "Map.h"
#include "Block.h"
#include "Math.h"

/// <summary>
/// <para>Map</para>
/// <para>�R���X�g���N�^</para>
/// </summary>
Map::Map(GameView* render)
{
	gameRender = render;
	// ������񏉊���
	nowHeight = 0;
	widthSize = START_WIDTH;
	moveDire = -1;
	floor = vector<FloorType>();
	floorCnt = 0;
	nowFloor = FloorType::Flat;

	// ����������
	Vector2 commonSize = Vector2(START_WIDTH, 1);
	Vector2 pos = Vector2(
		WIN_W_CENTOR + (START_WIDTH * OBJECT_SIZE) / HALF - OBJECT_SIZE,
		WIN_H - OBJECT_SIZE / HALF - (OBJECT_SIZE * 3)
	);
	blocks[0] = Block(&pos, &commonSize, gameRender);
	highestFloor = blocks[0].GetCollider();

	// �����v�[���Ő���
	commonSize = Vector2(2, 0.5);
	for (int i = 1;i < BLOCK_POOL;i++) {
		pos = Vector2(WIN_W_CENTOR, WIN_H + OBJECT_SIZE);
		blocks[i] = Block(&pos, &commonSize, gameRender);
	}

	// �����ʐݒ�
	length = BLOCK_POOL;

	// �J�����`��\�͈͂܂ŏ��𐶐�����
	while (BLOCK_HEIGHT_DIF - (OBJECT_SIZE / HALF) < highestFloor->pos.y) {
		CreateFloor();
	}
	
}

/// <summary>
/// <para>GetBlockListPtr</para>
/// <para>�z��̐擪�|�C���^���擾���܂�</para>
/// </summary>
/// <returns>�z��擪�|�C���^</returns>
Block* Map::GetBlockListPtr() {
	return blocks;
}

/// <summary>
/// <para>GetLength</para>
/// <para>�z��̒������擾���܂�</para>
/// </summary>
/// <returns>�z��̒���</returns>
int Map::GetLength() {
	return length;
}

/// <summary>
/// <para>View</para>
/// <para>�v���C���[��\������</para>
/// </summary>
/// <returns>������</returns>
bool Map::View()
{
	gameRender->SetDrowColor(WHITE);
	// ���݂̃u���b�N�̃|�C���^
	Block* nowBlock = blocks;

	// �z�񕪕`��
	for (int i = 0; i < length; i++)
	{
		// �|�C���^�擾
		nowBlock = blocks + i;

		// �`��Ɏ��s����
		if (!nowBlock->View()) 
		{
			return false;
		}
	}
	return true;
}

/// <summary>
/// <para>AddHeight</para>
/// <para>���ݍ��x�𑝉������܂�</para>
/// </summary>
/// <param name="val">�������x</param>
void Map::AddHeight(float val) {
	nowHeight += val;
	// �J�����`��\�͈͂܂ŏ��𐶐�����
	if (BLOCK_HEIGHT_DIF - (OBJECT_SIZE / HALF) < highestFloor->pos.y) {
		CreateFloor();
	}
}

/// <summary>
/// <para>GetHeight</para>
/// <para>���ݍ��x���擾���܂�</para>
/// </summary>
/// <returns>���ݍ��x</returns>
float Map::GetHeight() {
	return nowHeight;
}

/// <summary>
/// <para>CreateFloor</para>
/// <para>���𐶐����܂�</para>
/// </summary>
void Map::CreateFloor() {
	// �ŒZ�����L��
	if (MIN_WIDTH < widthSize) {
		widthSize -= MINUS_WIDTH;
	}
	moveDire = -moveDire;
	// ���̐����ʒu���m�肷��
	float nextFloorX = highestFloor->pos.x + ((highestFloor->GetWidth() / HALF) + ((widthSize / HALF) * OBJECT_SIZE) + BLOCK_WIDTH_DIF) * moveDire;
	// �����Ɍ덷���������邩
	if (Math::Random() == 1) {
		nextFloorX += NEXT_DIF * moveDire;
	}
	float nextFloorY = highestFloor->pos.y - BLOCK_HEIGHT_DIF;
	
	// �v�[������g�p�\�ȃu���b�N���擾
	Transform* settingBlock = GetUsableBlock();
	highestFloor = settingBlock;
	// �������
	Vector2 pos = Vector2(nextFloorX, nextFloorY);
	Vector2 size;

	nowFloor = GetFloorType();
	// �t���A�^�C�v���擾���āA����
	if (nowFloor == FloorType::Flat) {
		// ����ݒ�
		settingBlock->pos = pos;
		settingBlock->size = Vector2(widthSize, 1);
		settingBlock->Update();
		// �ǂ�ݒ�
		settingBlock = GetUsableBlock();
		pos = *pos.Add((((widthSize * OBJECT_SIZE) / HALF) + (OBJECT_SIZE / HALF)) * moveDire, -OBJECT_SIZE);
		settingBlock->pos = pos;
		settingBlock->size = WALL_SCALE;
		settingBlock->Update();
	}
	else {
		// ���^�C�v�̍ŏ�������
		float createWidth = MIN_FLOOR_HOLETYPE_WIDTH;
		// �ŏ����������ݒ肳��Ă��鐶�����̂ق����ł���
		if (createWidth < widthSize) {
			createWidth = widthSize;
		}

		// ����g�ݍ��񂾏��̒������v�Z
		float floorWidth = (createWidth - WIDTH_HOLE) / HALF;
		// ���̈ʒu���v�Z
		float floorDif = (OBJECT_SIZE * WIDTH_HOLE) / HALF + (OBJECT_SIZE * floorWidth) / HALF;
		
		// �i�s�������猩�āA��O�̏���ݒ�
		Vector2 flont = *pos.Add(-(floorDif * moveDire), 0);
		settingBlock->pos = flont;
		settingBlock->size = Vector2(floorWidth, 1);
		settingBlock->Update();
		// ���̏���ݒ�
		settingBlock = GetUsableBlock();
		Vector2 back = *pos.Add(floorDif * moveDire, 0);
		settingBlock->pos = back;
		settingBlock->size = Vector2(floorWidth, 1);
		settingBlock->Update();
		// �ǂ�ݒ�
		settingBlock = GetUsableBlock();
		pos = *pos.Add((((createWidth * OBJECT_SIZE) / HALF) + (OBJECT_SIZE / HALF)) * moveDire, -OBJECT_SIZE);
		settingBlock->pos = pos;
		settingBlock->size = WALL_SCALE;
		settingBlock->Update();
		
	}


}

/// <summary>
/// <para>GetFloorType</para>
/// <para>�t���A�^�C�v�𔠂�����o���܂�</para>
/// </summary>
/// <returns>�t���A�^�C�v</returns>
FloorType Map::GetFloorType() {
	// �S�Ď����
	if (floorCnt <= 0) {
		// ���^�C�v�������������肷��p
		bool inHole = false;
		// �T�C�N���̐����J��Ԃ�
		while (floorCnt < FLOOR_TYPE_CYCLE) {
			floorCnt++;
			// ���^�C�v����������
			if (inHole) {
				floor.push_back(FloorType::Flat);
				continue;
			}
			// �Ō�܂Ō��^�C�v�������Ă��Ȃ�
			if (!inHole && floorCnt == 2) {
				floor.push_back(FloorType::Hole);
				continue;
			}

			// �����_���擾
			int type = Math::Random();
			if (type == 1) {
				floor.push_back(FloorType::Hole);
				inHole = true;
				continue;
			}
			floor.push_back(FloorType::Flat);
		}
	}
	
	floorCnt--;
	// �t���A�^�C�v�擾
	FloorType returnType = floor[floorCnt];
	// �T�C�N������폜
	floor.pop_back();

	return returnType;
}

/// <summary>
/// <para>GetUsableBlock</para>
/// <para>�g�p�\�ȃu���b�N���擾���܂�</para>
/// </summary>
/// <returns></returns>
Transform* Map::GetUsableBlock() {
	Transform* returnBlock;

	// �u���b�N�̒��ŉ�ʊO�ɂ��镨���擾���܂�
	for (int i = 0;i < BLOCK_POOL;i++) {
		// �I�u�W�F�N�g���擾
		returnBlock = blocks[i].GetCollider();
		// ��ʊO�ɑ��݂��Ă���
		if (!returnBlock->ExistInScreen()) {
			// �g�p�\
			return returnBlock;
		}
	}
}