#pragma once
#include <time.h>
#include "Vector2.h"

// �v�Z�p
#define HALF 2

// ����include �w�b�_�[��
#define INPUT_H "GameInput.h"
#define RENDER_H "GameRender.h"
#define TRANSFORM_H "Transform.h"

// �J���[ID
#define WHITE 0
#define RED 1
#define GREEN 2
#define BLUE 3
#define PURPLE 4
#define YELLOW 5
#define CYAN 6
#define BLACK 7

// �E�B���h�E�ݒ�
#define WIN_NAME "C++ Action"
#define WIN_TOP_X 100
#define WIN_TOP_Y 50
// �E�B���h�E�T�C�Y
#define WIN_W 1280
#define WIN_H 720
// �E�B���h�E���S
#define WIN_W_CENTOR WIN_W / HALF
#define WIN_H_CENTOR WIN_H / HALF
// �w�i�J���[ID
#define BACKGROUND BLACK

// �I�u�W�F�N�g�̃T�C�Y
#define OBJECT_SIZE 50

//�Q�[�����
enum class GameStatus : int 
{
	Start,
	Play,
	Stop
};