#include "SDL.h"
#include "GameCommon.h"
#include INPUT_H

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
    SDL_PollEvent(&sdlEvent);
    const Uint8* state = SDL_GetKeyboardState(NULL);
    // 上ボタンを押した
    if (state[SDL_SCANCODE_UP]) {
        inputVal.y += BIG_JUMP;
    }
    // 下ボタンを押した
    if (state[SDL_SCANCODE_DOWN]) {
        inputVal.y += SMALL_JUMP;
    }
    // 終了ボタンを押した
    if (state[SDL_SCANCODE_ESCAPE]) {
        shutdown = true;
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