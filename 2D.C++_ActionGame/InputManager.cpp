#include "SDL.h"
#include "InputManager.h"


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

void Input::SetInputByPlayer() {
    inputVal.x = 0;
    inputVal.y = 0;
    //イベント取得
    SDL_Event sdlEvent;
    //取得できている かつ ボタンが押された
    if (SDL_PollEvent(&sdlEvent) && sdlEvent.type == SDL_KEYDOWN) {
        //右ボタンを押した
        if (sdlEvent.key.keysym.sym == SDLK_RIGHT) {
            inputVal.x = 1;
        }
        //左ボタンを押した
        if (sdlEvent.key.keysym.sym == SDLK_LEFT) {
            inputVal.x = -1;
        }
        //終了ボタンを押した
        if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
            shutdown = true;
        }
    }
}

Vector2 Input::GetInput() {
    return inputVal;
}

bool Input::GetDebug() {
    return shutdown;
}