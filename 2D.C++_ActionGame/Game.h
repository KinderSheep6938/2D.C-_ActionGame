#pragma once
//#include <cstdio>
//#include <cstdlib>
#include "SDL.h"
#include "GameCommon.h"
#include INPUT
#include RENDER
#include "Player.h"

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
	// Number of ticks since start of game
	Uint32 mTicksCount;

	// ゲームを描画します
	bool DrowGameView();
	// ゲームを再生します
	bool PlayGame(float deltaTime);
	// フレーム間隔時間を取得
	float DeltaTime();

};