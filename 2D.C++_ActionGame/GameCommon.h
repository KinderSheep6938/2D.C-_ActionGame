#pragma once
#include <time.h>

//����include �w�b�_�[��
#define INPUT "GameInput.h"
#define RENDER "GameRender.h"

//�E�B���h�E�ݒ�
#define WIN_NAME "C++ Action"
#define WIN_TOP_X 100
#define WIN_TOP_Y 50
//�E�B���h�E�T�C�Y
#define WIN_W 1280
#define WIN_H 720
//�E�B���h�E�� [�ŏ��l,�ő�l]
#define WIN_W_PER 0, WIN_W
#define WIN_H_PER 0, WIN_H

//�e�I�u�W�F�N�g�̃T�C�Y
#define PLAYER_SIZE 7.5
#define BLOCK_SIZE 7.5

//�J���[ID
#define WHITE 0
#define RED 1
#define GREEN 2
#define BLUE 3
#define PURPLE 4
#define YELLOW 5
#define CYAN 6
#define BLACK 7

//�v�Z�p
#define HALF 2

//���W
struct Vector2 
{
	float x;
	float y;
};

//�Q�[�����
enum class GameStatus : int 
{
	Start,
	Play,
	Stop
};