#pragma once
#include <time.h>
#include "Vector2.h"

// 計算用
#define HALF 2

// 共通include ヘッダー名
#define INPUT_H "GameInput.h"
#define RENDER_H "GameRender.h"
#define TRANSFORM_H "Transform.h"

// カラーID
#define WHITE 0
#define RED 1
#define GREEN 2
#define BLUE 3
#define PURPLE 4
#define YELLOW 5
#define CYAN 6
#define BLACK 7

// ウィンドウ設定
#define WIN_NAME "C++ Action"
#define WIN_TOP_X 100
#define WIN_TOP_Y 50
// ウィンドウサイズ
#define WIN_W 1280
#define WIN_H 720
// ウィンドウ中心
#define WIN_W_CENTOR WIN_W / HALF
#define WIN_H_CENTOR WIN_H / HALF
// 背景カラーID
#define BACKGROUND BLACK

// オブジェクトのサイズ
#define OBJECT_SIZE 50

//ゲーム状態
enum class GameStatus : int 
{
	Start,
	Play,
	Stop
};