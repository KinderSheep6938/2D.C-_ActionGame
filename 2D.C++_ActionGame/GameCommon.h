#pragma once
#include <time.h>

//共通include ヘッダー名
#define INPUT "GameInput.h"
#define RENDER "GameRender.h"

//ウィンドウ設定
#define WIN_NAME "C++ Action"
#define WIN_TOP_X 100
#define WIN_TOP_Y 50
//ウィンドウサイズ
#define WIN_W 1280
#define WIN_H 720
//ウィンドウ幅 [最小値,最大値]
#define WIN_W_PER 0, WIN_W
#define WIN_H_PER 0, WIN_H

//各オブジェクトのサイズ
#define PLAYER_SIZE 7.5
#define BLOCK_SIZE 7.5

//カラーID
#define WHITE 0
#define RED 1
#define GREEN 2
#define BLUE 3
#define PURPLE 4
#define YELLOW 5
#define CYAN 6
#define BLACK 7

//計算用
#define HALF 2

//座標
struct Vector2 
{
	float x;
	float y;
};

//ゲーム状態
enum class GameStatus : int 
{
	Start,
	Play,
	Stop
};