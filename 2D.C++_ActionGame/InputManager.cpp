#include "SDL.h"
#include "GameCommon.h"
#include INPUT

//�ړ���
#define MOVE_P 1000
#define MOVE_M -1000

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
    // �擾�ł��Ă��� ���� �{�^���������ꂽ
    if (SDL_PollEvent(&sdlEvent) && sdlEvent.type == SDL_KEYDOWN) {
        // �E�{�^����������
        if (sdlEvent.key.keysym.sym == SDLK_RIGHT) {
            inputVal.x += MOVE_P;
        }
        // ���{�^����������
        if (sdlEvent.key.keysym.sym == SDLK_LEFT) {
            inputVal.x += MOVE_M;
        }
        // ��{�^����������
        if (sdlEvent.key.keysym.sym == SDLK_UP) {
            inputVal.y += MOVE_M;
        }
        // ���{�^����������
        if (sdlEvent.key.keysym.sym == SDLK_DOWN) {
            inputVal.y += MOVE_P;
        }
        // �I���{�^����������
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