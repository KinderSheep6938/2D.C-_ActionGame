#pragma once
//#include <cstdio>
//#include <cstdlib>
#include "SDL.h"
#include "GameCommon.h"
#include INPUT_H
#include RENDER_H
#include "Player.h"
#include "Map.h"
#include "ColliderManager.h"
#include "Camera.h"

/// <summary>
/// <para>Game</para>
/// <para>ゲームの管理クラス</para>
/// </summary>
class Game 
{
public:
	Game();
	// ゲームを初期化する
	GameStatus Initialize();
	// ゲームループ
	GameStatus RunGame();
	// ゲームを終了する
	void Shutdown();
	// ゲームビューを渡す
	GameView* GetGameView();

private:
	// ゲームビュー
	GameView* gameView;
	// 入力管理マネージャー
	Input* input;
	// プレイヤー
	Player* player;
	// マップ
	Map* map;
	// 衝突管理
	ColliderManager* collManager;
	// ガメラ
	Camera* camera;

	// Number of ticks since start of game
	Uint32 mTicksCount;
	//描画更新処理
	bool needRender;


	// ゲームを描画します
	bool DrowGameView();
	// ゲームを再生します
	bool PlayGame(float deltaTime);
	// カメラなどに反映させます
	bool Output();
	// フレーム間隔時間を取得
	float DeltaTime();

};