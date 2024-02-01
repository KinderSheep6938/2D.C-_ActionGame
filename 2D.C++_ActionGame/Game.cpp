#include "Game.h"

/// <summary>
/// <para>Game</para>
/// <para>コンストラクタ</para>
/// </summary>
Game::Game()
{
	mWindow = nullptr;
	mRenderer = nullptr;
	mTicksCount = 0;
	mIsRunning = true;
}

/// <summary>
/// <para>Initialize</para>
/// <para>ゲームの初期化処理</para>
/// </summary>
/// <returns>処理成功判定</returns>
GameStatus Game::Initialize() {
	// SDL初期化
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	// 初期化に失敗した
	if (sdlResult != 0) {
		SDL_Log("SDLを初期化できません : %s", SDL_GetError());
		return Stop;
	}

	// SDLウィンドウを作成
	mWindow = SDL_CreateWindow(
		WIN_NAME, // ウィンドウのタイトル
		WIN_TOP_X, // ウィンドウ左上隅のx座標
		WIN_TOP_Y, // ウィンドウ左上隅のy座標
		WIN_W, // ウィンドウの幅(width)
		WIN_H, // ウィンドウの高さ(height)
		0 // フラグ(設定しない時は0)
	);

	// 生成に失敗した
	if (!mWindow) {
		SDL_Log("ウィンドウの作成に失敗しました : %s", SDL_GetError());
		return Stop;
	}

	// SDLレンダラーを作成
	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	return Play;
}

/// <summary>
/// <para>RunGame</para>
/// <para>ゲームのプレイ処理</para>
/// </summary>
void Game::RunGame() {
	SDL_SetRenderDrawColor(mRenderer, 0xdf, 0xff, 0xdf, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(mRenderer);
	/* 線の描画 */
	SDL_SetRenderDrawColor(mRenderer, 0xff, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(mRenderer, 0, 0, 319, 239);
	SDL_RenderPresent(mRenderer);
}

/// <summary>
/// <para>Shutdown</para>
/// <para>ゲームの終了処理</para>
/// </summary>
void Game::Shutdown() {

	if (mRenderer) SDL_DestroyRenderer(mRenderer);
	if (mWindow) SDL_DestroyWindow(mWindow);

	SDL_Quit();
}
