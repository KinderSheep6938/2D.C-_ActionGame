#pragma once

//�E�B���h�E�T�C�Y
#define WIN_W 1280
#define WIN_H 720

//�e�I�u�W�F�N�g�̃T�C�Y
#define PLAYER_SIZE = 0.5
#define BLOCK_SIZE = 0.5

//���W
struct Vector2 {
	float x;
	float y;
};

//�Q�[�����
enum GameStatus {
	Start,
	Play,
	Stop
};