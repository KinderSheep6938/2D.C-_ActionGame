#pragma once
#include "SDL.h"
#include "GameCommon.h"


//カラーコード
#define BLACK_C 0,0,0
#define RED_C 0xff,0,0
#define GREEN_C 0,0xff,0
#define BLUE_C 0,0,0xff
#define PURPLE_C 0xff,0,0xff
#define YELLOW_C 0xff,0xff,0
#define CYAN_C 0,0xff,0xff
#define WHITE_C 0xff,0xff,0xff 

/// <summary>
/// <para>GameView</para>
/// <para>ゲームの管理クラス</para>
/// </summary>
class GameView 
{
public:
	GameView();
	// ゲームビューを初期化
	GameStatus Initialize();
	// ゲームビューを削除
	void Shutdown();

	// 画面クリア
	bool Clear();
	// 画面更新
	void Update();
	// 描画色設定
	void SetDrowColor(int color);
	// 四角描画
	void DrowSquare(Vector2* pos, Vector2* size, float gameScale);

	// ゲームウィンドウを取得
	SDL_Window* GetWindow();
	// 描画レンダリングを取得
	SDL_Renderer* GetRenderer();

private:
	// SDLが作るウィンドウ
	SDL_Window* mWindow;
	// 2D描画のためのレンダリング
	SDL_Renderer* mRenderer;
	// 現在設定されている描画色
	int colorId;

};