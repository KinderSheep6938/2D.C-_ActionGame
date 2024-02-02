#include "SDL.h"
#include "GameCommon.h"
#include INPUT

//移動量
#define MOVE_P 1000
#define MOVE_M -1000

/// <summary>
/// <para>Input</para>
/// <para>コンストラクタ</para>
/// </summary>
Input::Input() 
{
	inputVal.x = 0;
	inputVal.y = 0;
	shutdown = false;
}

void Input::SetInputByPlayer() 
{
    inputVal.x = 0;
    inputVal.y = 0;
    // イベント取得
    SDL_Event sdlEvent;
    // 取得できている かつ ボタンが押された
    if (SDL_PollEvent(&sdlEvent) && sdlEvent.type == SDL_KEYDOWN) {
        // 右ボタンを押した
        if (sdlEvent.key.keysym.sym == SDLK_RIGHT) {
            inputVal.x += MOVE_P;
        }
        // 左ボタンを押した
        if (sdlEvent.key.keysym.sym == SDLK_LEFT) {
            inputVal.x += MOVE_M;
        }
        // 上ボタンを押した
        if (sdlEvent.key.keysym.sym == SDLK_UP) {
            inputVal.y += MOVE_M;
        }
        // 下ボタンを押した
        if (sdlEvent.key.keysym.sym == SDLK_DOWN) {
            inputVal.y += MOVE_P;
        }
        // 終了ボタンを押した
        if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
            shutdown = true;
        }
    }
}

Vector2* Input::GetInput() 
{
    return &inputVal;
}

bool Input::GetDebug() 
{
    return shutdown;
}