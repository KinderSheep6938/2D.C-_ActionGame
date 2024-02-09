#include "Map.h"
#include "Block.h"
#include "Math.h"

/// <summary>
/// <para>Map</para>
/// <para>コンストラクタ</para>
/// </summary>
Map::Map(GameView* render)
{
	gameRender = render;
	// 生成情報初期化
	nowHeight = 0;
	widthSize = START_WIDTH;
	moveDire = -1;
	floor = vector<FloorType>();
	floorCnt = 0;
	nowFloor = FloorType::Flat;

	// 初期床生成
	Vector2 commonSize = Vector2(START_WIDTH, 1);
	Vector2 pos = Vector2(
		WIN_W_CENTOR + (START_WIDTH * OBJECT_SIZE) / HALF - OBJECT_SIZE,
		WIN_H - OBJECT_SIZE / HALF - (OBJECT_SIZE * 3)
	);
	blocks[0] = Block(&pos, &commonSize, gameRender);
	highestFloor = blocks[0].GetCollider();

	// 床をプールで生成
	commonSize = Vector2(2, 0.5);
	for (int i = 1;i < BLOCK_POOL;i++) {
		pos = Vector2(WIN_W_CENTOR, WIN_H + OBJECT_SIZE);
		blocks[i] = Block(&pos, &commonSize, gameRender);
	}

	// 生成量設定
	length = BLOCK_POOL;

	// カメラ描画可能範囲まで床を生成する
	while (BLOCK_HEIGHT_DIF - (OBJECT_SIZE / HALF) < highestFloor->pos.y) {
		CreateFloor();
	}
	
}

/// <summary>
/// <para>GetBlockListPtr</para>
/// <para>配列の先頭ポインタを取得します</para>
/// </summary>
/// <returns>配列先頭ポインタ</returns>
Block* Map::GetBlockListPtr() {
	return blocks;
}

/// <summary>
/// <para>GetLength</para>
/// <para>配列の長さを取得します</para>
/// </summary>
/// <returns>配列の長さ</returns>
int Map::GetLength() {
	return length;
}

/// <summary>
/// <para>View</para>
/// <para>プレイヤーを表示する</para>
/// </summary>
/// <returns>成功可否</returns>
bool Map::View()
{
	gameRender->SetDrowColor(WHITE);
	// 現在のブロックのポインタ
	Block* nowBlock = blocks;

	// 配列分描画
	for (int i = 0; i < length; i++)
	{
		// ポインタ取得
		nowBlock = blocks + i;

		// 描画に失敗した
		if (!nowBlock->View()) 
		{
			return false;
		}
	}
	return true;
}

/// <summary>
/// <para>AddHeight</para>
/// <para>現在高度を増加させます</para>
/// </summary>
/// <param name="val">増加高度</param>
void Map::AddHeight(float val) {
	nowHeight += val;
	// カメラ描画可能範囲まで床を生成する
	if (BLOCK_HEIGHT_DIF - (OBJECT_SIZE / HALF) < highestFloor->pos.y) {
		CreateFloor();
	}
}

/// <summary>
/// <para>GetHeight</para>
/// <para>現在高度を取得します</para>
/// </summary>
/// <returns>現在高度</returns>
float Map::GetHeight() {
	return nowHeight;
}

/// <summary>
/// <para>CreateFloor</para>
/// <para>床を生成します</para>
/// </summary>
void Map::CreateFloor() {
	// 最短幅より広い
	if (MIN_WIDTH < widthSize) {
		widthSize -= MINUS_WIDTH;
	}
	moveDire = -moveDire;
	// 次の生成位置を確定する
	float nextFloorX = highestFloor->pos.x + ((highestFloor->GetWidth() / HALF) + ((widthSize / HALF) * OBJECT_SIZE) + BLOCK_WIDTH_DIF) * moveDire;
	// 横幅に誤差を持たせるか
	if (Math::Random() == 1) {
		nextFloorX += NEXT_DIF * moveDire;
	}
	float nextFloorY = highestFloor->pos.y - BLOCK_HEIGHT_DIF;
	
	// プールから使用可能なブロックを取得
	Transform* settingBlock = GetUsableBlock();
	highestFloor = settingBlock;
	// 生成情報
	Vector2 pos = Vector2(nextFloorX, nextFloorY);
	Vector2 size;

	nowFloor = GetFloorType();
	// フロアタイプを取得して、生成
	if (nowFloor == FloorType::Flat) {
		// 床を設定
		settingBlock->pos = pos;
		settingBlock->size = Vector2(widthSize, 1);
		settingBlock->Update();
		// 壁を設定
		settingBlock = GetUsableBlock();
		pos = *pos.Add((((widthSize * OBJECT_SIZE) / HALF) + (OBJECT_SIZE / HALF)) * moveDire, -OBJECT_SIZE);
		settingBlock->pos = pos;
		settingBlock->size = WALL_SCALE;
		settingBlock->Update();
	}
	else {
		// 穴タイプの最小生成幅
		float createWidth = MIN_FLOOR_HOLETYPE_WIDTH;
		// 最小生成幅より設定されている生成幅のほうがでかい
		if (createWidth < widthSize) {
			createWidth = widthSize;
		}

		// 穴を組み込んだ床の長さを計算
		float floorWidth = (createWidth - WIDTH_HOLE) / HALF;
		// 床の位置を計算
		float floorDif = (OBJECT_SIZE * WIDTH_HOLE) / HALF + (OBJECT_SIZE * floorWidth) / HALF;
		
		// 進行方向から見て、手前の床を設定
		Vector2 flont = *pos.Add(-(floorDif * moveDire), 0);
		settingBlock->pos = flont;
		settingBlock->size = Vector2(floorWidth, 1);
		settingBlock->Update();
		// 奥の床を設定
		settingBlock = GetUsableBlock();
		Vector2 back = *pos.Add(floorDif * moveDire, 0);
		settingBlock->pos = back;
		settingBlock->size = Vector2(floorWidth, 1);
		settingBlock->Update();
		// 壁を設定
		settingBlock = GetUsableBlock();
		pos = *pos.Add((((createWidth * OBJECT_SIZE) / HALF) + (OBJECT_SIZE / HALF)) * moveDire, -OBJECT_SIZE);
		settingBlock->pos = pos;
		settingBlock->size = WALL_SCALE;
		settingBlock->Update();
		
	}


}

/// <summary>
/// <para>GetFloorType</para>
/// <para>フロアタイプを箱から取り出します</para>
/// </summary>
/// <returns>フロアタイプ</returns>
FloorType Map::GetFloorType() {
	// 全て取った
	if (floorCnt <= 0) {
		// 穴タイプが入ったか判定する用
		bool inHole = false;
		// サイクルの数分繰り返す
		while (floorCnt < FLOOR_TYPE_CYCLE) {
			floorCnt++;
			// 穴タイプが入ったか
			if (inHole) {
				floor.push_back(FloorType::Flat);
				continue;
			}
			// 最後まで穴タイプが入っていない
			if (!inHole && floorCnt == 2) {
				floor.push_back(FloorType::Hole);
				continue;
			}

			// ランダム取得
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
	// フロアタイプ取得
	FloorType returnType = floor[floorCnt];
	// サイクルから削除
	floor.pop_back();

	return returnType;
}

/// <summary>
/// <para>GetUsableBlock</para>
/// <para>使用可能なブロックを取得します</para>
/// </summary>
/// <returns></returns>
Transform* Map::GetUsableBlock() {
	Transform* returnBlock;

	// ブロックの中で画面外にある物を取得します
	for (int i = 0;i < BLOCK_POOL;i++) {
		// オブジェクト情報取得
		returnBlock = blocks[i].GetCollider();
		// 画面外に存在している
		if (!returnBlock->ExistInScreen()) {
			// 使用可能
			return returnBlock;
		}
	}
}