#include "Game.h"

int main(int argc, char** argv) 
{
	//�Q�[���Ǘ��N���X
	Game game;

	GameStatus nowGame = GameStatus::Start;
	//�Q�[��������
	nowGame = game.Initialize();

	//�Q�[�����v���C�ł���
	while (nowGame == GameStatus::Play) {
		//�Q�[�����v���C
		nowGame = game.RunGame();
	}

	//�Q�[���I��
	game.Shutdown();
	return 0;
}