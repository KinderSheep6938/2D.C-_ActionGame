#pragma once
//#include <cstdio>
//#include <cstdlib>
#include "SDL.h"
#include "GameCommon.h"

//ウィンドウ設定
#define WIN_NAME "C++ Action"
#define WIN_TOP_X 100
#define WIN_TOP_Y 50

/// <summary>
/// <para>Game</para>
/// <para>ゲームの管理クラス</para>
/// </summary>
class Game {
public:
	Game();
	//ゲームを初期化する
	GameStatus Initialize();
	//ゲームループ
	void RunGame();
	//ゲームを終了する
	void Shutdown();

private:
	//SDLが作るウィンドウ
	SDL_Window* mWindow;
	//2D描画のためのレンダリング
	SDL_Renderer* mRenderer;
	// Number of ticks since start of game
	Uint32 mTicksCount;
	//ゲームの続行を支持する
	bool mIsRunning;

};