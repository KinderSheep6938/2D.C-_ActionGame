#include "SDL.h"
#include "InputManager.h"


/// <summary>
/// <para>Input</para>
/// <para>�R���X�g���N�^</para>
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
    //�C�x���g�擾
    SDL_Event sdlEvent;
    //�擾�ł��Ă��� ���� �{�^���������ꂽ
    if (SDL_PollEvent(&sdlEvent) && sdlEvent.type == SDL_KEYDOWN) {
        //�E�{�^����������
        if (sdlEvent.key.keysym.sym == SDLK_RIGHT) {
            inputVal.x = 1;
        }
        //���{�^����������
        if (sdlEvent.key.keysym.sym == SDLK_LEFT) {
            inputVal.x = -1;
        }
        //�I���{�^����������
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