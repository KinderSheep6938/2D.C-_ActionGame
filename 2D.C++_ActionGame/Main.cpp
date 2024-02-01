#include "Game.h"
#include "InputManager.h"

int main(int argc, char** argv) {
	//ゲームクラス
	Game game;
	//入力
	Input input;

	GameStatus nowGame = Start;
	//ゲーム初期化
	nowGame = game.Initialize();

	//ゲームをプレイできる
	while (nowGame == Play) {
		//プレイヤー入力反映
		input.SetInputByPlayer();
		
		//終了キー
		if (input.GetDebug()) {
			nowGame = Stop;
			break;
		}

		//ゲームをプレイ
		game.RunGame();
	}

	//ゲーム終了
	game.Shutdown();
	return 0;
}