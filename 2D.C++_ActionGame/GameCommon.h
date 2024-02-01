#pragma once

//ウィンドウサイズ
#define WIN_W 1280
#define WIN_H 720

//各オブジェクトのサイズ
#define PLAYER_SIZE = 0.5
#define BLOCK_SIZE = 0.5

//座標
struct Vector2 {
	float x;
	float y;
};

//ゲーム状態
enum GameStatus {
	Start,
	Play,
	Stop
};