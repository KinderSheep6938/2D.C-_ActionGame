#include "SDL.h"
#include "GameCommon.h"
#include INPUT_H

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

void Input::SetInputByPlayer() 
{
    inputVal.x = 0;
    inputVal.y = 0;
    // �C�x���g�擾
    SDL_Event sdlEvent;
    SDL_PollEvent(&sdlEvent);
    const Uint8* state = SDL_GetKeyboardState(NULL);
    // ��{�^����������
    if (state[SDL_SCANCODE_UP]) {
        inputVal.y += BIG_JUMP;
    }
    // ���{�^����������
    if (state[SDL_SCANCODE_DOWN]) {
        inputVal.y += SMALL_JUMP;
    }
    // �I���{�^����������
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