#include "Game.h"
#include "InputManager.h"

int main(int argc, char** argv) {
	//�Q�[���N���X
	Game game;
	//����
	Input input;

	GameStatus nowGame = Start;
	//�Q�[��������
	nowGame = game.Initialize();

	//�Q�[�����v���C�ł���
	while (nowGame == Play) {
		//�v���C���[���͔��f
		input.SetInputByPlayer();
		
		//�I���L�[
		if (input.GetDebug()) {
			nowGame = Stop;
			break;
		}

		//�Q�[�����v���C
		game.RunGame();
	}

	//�Q�[���I��
	game.Shutdown();
	return 0;
}