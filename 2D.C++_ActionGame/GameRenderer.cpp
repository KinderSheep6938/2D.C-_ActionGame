#include "GameCommon.h"
#include RENDER_H
#include <filesystem>
#include <iostream>

#define SKY_POS Vector2(0,0)
#define GROUND_POS Vector2(0, WIN_H_CENTOR + WIN_H_CENTOR / HALF)
#define SCROLL_SPEED 3

/// <summary>
/// <para>GameView</para>
/// <para>コンストラクタ</para>
/// </summary>
GameView::GameView()
{

	mWindow = nullptr;
	mRenderer = nullptr;
	image = nullptr;
	imageTexture = nullptr;
	colorId = WHITE;
}

/// <summary>
/// <para>Initialize</para>
/// <para>ゲームビューを初期化します</para>
/// </summary>
/// <returns>処理成功判定</returns>
GameStatus GameView::Initialize() 
{
	// SDL初期化
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	// 初期化に失敗した
	if (sdlResult != 0) {
		SDL_Log("SDLを初期化できません : %s", SDL_GetError());
		return GameStatus::Stop;
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
		return GameStatus::Stop;
	}

	// SDLレンダラーを作成
	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	return GameStatus::Play;
}

/// <summary>
/// <para>Shutdown</para>
/// <para>ゲームビューの終了させます</para>
/// </summary>
void GameView::Shutdown() 
{
	if (mRenderer) SDL_DestroyRenderer(mRenderer);
	if (mWindow) SDL_DestroyWindow(mWindow);

	SDL_Quit();
}

/// <summary>
/// <para>GetWindow</para>
/// <para>ゲームウィンドウを取得します</para>
/// </summary>
SDL_Window* GameView::GetWindow() 
{
	return mWindow;
}

/// <summary>
/// <para>GetRenderer</para>
/// <para>レンダリングを取得します</para>
/// </summary>
SDL_Renderer* GameView::GetRenderer()
{
	return mRenderer;
}

/// <summary>
/// <para>Clear</para>
/// <para>画面を所定の画面に初期化します</para>
/// </summary>
/// <returns>成功可否</returns>
bool GameView::Clear(float height) 
{
	//NULLチェック
	if (!mRenderer) 
	{
		return false;
	}

	SetDrowColor(CYAN);
	SDL_RenderClear(mRenderer);
	/* 線の描画 */

	Vector2 drowPos = SKY_POS;
	SetDrowColor(BLUE);
	DrowSquare(&drowPos, WIN_W, (WIN_H_CENTOR / HALF) - height / SCROLL_SPEED / HALF);
	SetDrowColor(BLACK);
	DrowSquare(&drowPos, WIN_W, -height / SCROLL_SPEED / SCROLL_SPEED);
	drowPos = *GROUND_POS.Add(0, -height / SCROLL_SPEED);
	SetDrowColor(GREEN);
	DrowSquare(&drowPos, WIN_W, WIN_H);

	return true;
}

/// <summary>
/// <para>Update</para>
/// <para>画面を更新します</para>
/// </summary>
void GameView::Update()
{
	SDL_RenderPresent(mRenderer);
}

/// <summary>
/// <para>SetDrowColor</para>
/// <para>描画色を設定します</para>
/// </summary>
/// <param name="color">設定する色</param>
void GameView::SetDrowColor(int color)
{
	// 同じ描画色の場合は処理しない
	if (colorId == color) return;

	// 色ごとに設定
	switch (color)
	{
	case WHITE:		// 白
		SDL_SetRenderDrawColor(mRenderer, WHITE_C , SDL_ALPHA_OPAQUE);
		break;

	case RED:		// 赤
		SDL_SetRenderDrawColor(mRenderer, RED_C, SDL_ALPHA_OPAQUE);
		break;

	case GREEN:		// 緑
		SDL_SetRenderDrawColor(mRenderer, GREEN_C, SDL_ALPHA_OPAQUE);
		break;

	case BLUE:		// 青
		SDL_SetRenderDrawColor(mRenderer, BLUE_C, SDL_ALPHA_OPAQUE);
		break;

	case PURPLE:	// 紫
		SDL_SetRenderDrawColor(mRenderer, PURPLE_C, SDL_ALPHA_OPAQUE);
		break;

	case YELLOW:	// 黄
		SDL_SetRenderDrawColor(mRenderer, YELLOW_C, SDL_ALPHA_OPAQUE);
		break;

	case CYAN:		// 水
		SDL_SetRenderDrawColor(mRenderer, CYAN_C, SDL_ALPHA_OPAQUE);
		break;

	case BLACK:		// 黒
		SDL_SetRenderDrawColor(mRenderer, BLACK_C, SDL_ALPHA_OPAQUE);
		break;

	default:
		//例外は白に設定
		SDL_SetRenderDrawColor(mRenderer, WHITE_C, SDL_ALPHA_OPAQUE);
		break;
	}
	colorId = color;
}

/// <summary>
/// <para>SetDrowSquare</para>
/// <para>単色の四角を描画します</para>
/// </summary>
/// <param name="pos">座標</param>
/// <param name="size">大きさ</param>
void GameView::DrowSquare(Vector2* topEdge,float width,float height)
{
	// 描画情報設定
	SDL_Rect rect = SDL_Rect();
	rect.x = topEdge->x;
	rect.y = topEdge->y;
	rect.w = width;
	rect.h = height;

	// 描画
	SDL_RenderFillRect(mRenderer, &rect);
}

void GameView::DrowText(int val) {

	
	// 画像の読み込み
	
	return;
}

/// <summary>
/// <para>FloatPermission</para>
/// <para>入力値を最小最大値内に収めます</para>
/// </summary>
/// <param name="value">入力値</param>
/// <param name="bottom">最小値</param>
/// <param name="top">最大値</param>
/// <returns>補正された入力値</returns>
void FloatPermission(float* value, float* bottom, float* top)
{
	// 最小値より小さい
	if (value < bottom)
	{
		value = bottom;
		return;
	}

	// 最大値より大きい
	if (top < value)
	{
		value = top;
		return;
	}
}

