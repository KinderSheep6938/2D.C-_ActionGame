#include "Game.h"

int main(int argc, char** argv) 
{
	//ゲーム管理クラス
	Game game;

	GameStatus nowGame = GameStatus::Start;
	//ゲーム初期化
	nowGame = game.Initialize();

	//ゲームをプレイできる
	while (nowGame == GameStatus::Play) {
		//ゲームをプレイ
		nowGame = game.RunGame();
	}

	//ゲーム終了
	game.Shutdown();
	return 0;
}