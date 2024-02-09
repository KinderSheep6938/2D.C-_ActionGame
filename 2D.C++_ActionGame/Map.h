#pragma once
#include "GameCommon.h"
#include RENDER_H
#include "Block.h"
#include <vector>

using namespace std;

// ブロック数
#define BLOCK_POOL 20

// ブロック生成位置のズレ
#define BLOCK_HEIGHT_DIF (OBJECT_SIZE * 3.5)
#define BLOCK_WIDTH_DIF OBJECT_SIZE

// マップ生成の基本情報
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
/// <para>マップを管理します</para>
/// </summary>
class Map
{
public:
	Map(GameView* render);
	
	// 表示
	bool View();
	// 高さ更新
	void AddHeight(float val);
	// 高さ取得
	float GetHeight();

	// ブロックのオブジェクト情報の取得
	Block* GetBlockListPtr();
	// ブロック配列の長さ
	int GetLength();

private:
	// ブロック管理の配列
	Block blocks[BLOCK_POOL];
	// 配列長
	int length;
	// 一番高いフロア
	Transform* highestFloor;

	// 現在の高さ
	float nowHeight;
	// オブジェクト横幅
	float widthSize;
	// 進行方向
	int moveDire;
	// フロア周期配列
	vector<FloorType> floor;
	// フロア周期カウント
	int floorCnt;
	// 前回のフロアタイプ保存
	FloorType nowFloor;

	// レンダリング
	GameView* gameRender;

	// フロア生成
	void CreateFloor();
	// フロアタイプ取得
	FloorType GetFloorType();
	// 使用可能なブロックを返却
	Transform* GetUsableBlock();
};