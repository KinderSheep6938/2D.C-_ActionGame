#include "Game.h"
#include RENDER
#include INPUT
#include "Player.h"

/// <summary>
/// <para>Game</para>
/// <para>コンストラクタ</para>
/// </summary>
Game::Game()
{
	gameView = new GameView();
	input = new Input();
	player = new Player(gameView);
	mTicksCount = SDL_GetTicks();
}

/// <summary>
/// <para>Initialize</para>
/// <para>ゲームの初期化処理</para>
/// </summary>
/// <returns>処理成功判定</returns>
GameStatus Game::Initialize() 
{
	// ゲームビュー初期化
	GameStatus init = gameView->Initialize();
	
	return init;
}

/// <summary>
/// <para>RunGame</para>
/// <para>ゲームのプレイ処理</para>
/// </summary>
GameStatus Game::RunGame() 
{
	//入力受付
	input->SetInputByPlayer();

	//終了キー
	if (input->GetDebug()) {
		return GameStatus::Stop;
	}

	//描画処理
	if (!DrowGameView()) {
		return GameStatus::Stop;
	}

	float deltaTime = DeltaTime();
	//ゲーム処理
	if (!PlayGame(deltaTime)) {
		return GameStatus::Stop;
	}


	return GameStatus::Play;
}

/// <summary>
/// <para>SetView</para>
/// <para>ゲームを描画します</para>
/// </summary>
/// <returns></returns>
bool Game::DrowGameView() 
{
	//スクリーンクリア
	if (!gameView->Clear()) {
		return false;
	}
	//プレイヤー描画
	if (!player->View()) {
		return false;
	}

	return true;
}

bool Game::PlayGame(float deltaTime) 
{
	//プレイヤー移動
	player->Move(input->GetInput(), deltaTime);

	return true;
}

float Game::DeltaTime() 
{
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	//時刻を更新
	mTicksCount = SDL_GetTicks();

	return deltaTime;
}


/// <summary>
/// <para>Shutdown</para>
/// <para>ゲームの終了処理</para>
/// </summary>
void Game::Shutdown() 
{
	// ゲームビュー削除
	gameView->Shutdown();
}

/// <summary>
/// <para>GetGameView</para>
/// <para>ゲームビューを取得します</para>
/// </summary>
/// <returns>ゲームビューのポインタ</returns>
GameView* Game::GetGameView() 
{
	return gameView;
}
