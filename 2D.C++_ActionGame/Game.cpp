#include "Game.h"

#define START_POS_X (WIN_H / HALF)
#define START_POS_Y 74.9

/// <summary>
/// <para>Game</para>
/// <para>コンストラクタ</para>
/// </summary>
Game::Game()
{
	// 表示関連
	gameView = new GameView();

	// マップ関連
	map = new Map(gameView);
	collManager = new ColliderManager(map->GetBlockListPtr(),map->GetLength());

	// プレイヤー関連
	input = new Input();
	Vector2 sPos = Vector2(WIN_W_CENTOR, WIN_H_CENTOR);
	Vector2 sSize = VECTOR_ONE;
	player = new Player(&sPos, &sSize, gameView, collManager);

	// アウトプット
	camera = new Camera(player, map->GetBlockListPtr());

	mTicksCount = SDL_GetTicks();
	needRender = true;
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

	//描画処理
	if (!DrowGameView()) {
		return GameStatus::Stop;
	}
	
	return init;
}

/// <summary>
/// <para>RunGame</para>
/// <para>ゲームのプレイ処理</para>
/// </summary>
GameStatus Game::RunGame() 
{
	//60FPS待機
	if (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16)) {
		return GameStatus::Play;
	}

	float deltaTime = DeltaTime();
	//入力受付
	input->SetInputByPlayer();

	//終了キー
	if (input->GetDebug()) {
		return GameStatus::Stop;
	}

	//ゲーム処理
	if (!PlayGame(deltaTime)) {
		return GameStatus::Stop;
	}

	if (!Output()) {
		return GameStatus::Stop;
	}

	//描画処理
	if (!DrowGameView()) {
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
	//描画更新確認
	if (!needRender) {
		return true;
	}

	// スクリーンクリア
	if (!gameView->Clear(map->GetHeight())) {
		return false;
	}

	// プレイヤー描画
	if (!player->View()) {
		return false;
	}

	// マップ描画
	if (!map->View()) {
		return false;
	}

	gameView->DrowText(0);

	gameView->Update();

	return true;
}

/// <summary>
/// <para>PlayGame</para>
/// <para>ゲームのプレイ処理を行います</para>
/// </summary>
/// <param name="deltaTime"></param>
/// <returns></returns>
bool Game::PlayGame(float deltaTime) 
{
	// 入力取得
	Vector2* set = input->GetInput();

	// プレイヤー反映
	player->Move(set, deltaTime);

	return true;
}

/// <summary>
/// <para>Output</para>
/// <para>ゲームプレイ結果を画面に反映させます</para>
/// </summary>
bool Game::Output() 
{
	// 横軸の移動量
	float holizontalVal = player->GetCollider()->pos.x - WIN_W_CENTOR;
	// 縦軸の移動量
	float verticalVal = 0;
	// 高度更新ラインを超えた
	if (player->GetCollider()->pos.y < WIN_H_CENTOR - OBJECT_SIZE) {
		verticalVal = player->GetCollider()->pos.y - (WIN_H_CENTOR - OBJECT_SIZE);
		// 現在高度更新
		map->AddHeight(verticalVal);
	}

	// スクロール量
	Vector2 scrollVal = Vector2(-holizontalVal, -verticalVal);
	camera->Scroll(&scrollVal);

	// 画面内にプレイヤーが存在しない
	if (!player->GetCollider()->ExistInScreen()) {
		return false;
	}
	return true;
}

/// <summary>
/// <para>DeltaTime</para>
/// <para>フレーム経過時間</para>
/// </summary>
/// <returns></returns>
float Game::DeltaTime() 
{
	//前フレームから16msが経過するまで待つ
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	//時刻を更新
	mTicksCount = SDL_GetTicks();

	//デルタタイムを最大値で制限する
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}

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
