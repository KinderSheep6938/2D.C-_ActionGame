#include "Game.h"
#include RENDER
#include INPUT
#include "Player.h"

/// <summary>
/// <para>Game</para>
/// <para>�R���X�g���N�^</para>
/// </summary>
Game::Game()
{
	gameView = new GameView();
	input = new Input();
	player = new Player(gameView);
	mTicksCount = SDL_GetTicks();
}

/// <summary>
/// <para>Initialize</para>
/// <para>�Q�[���̏���������</para>
/// </summary>
/// <returns>������������</returns>
GameStatus Game::Initialize() 
{
	// �Q�[���r���[������
	GameStatus init = gameView->Initialize();
	
	return init;
}

/// <summary>
/// <para>RunGame</para>
/// <para>�Q�[���̃v���C����</para>
/// </summary>
GameStatus Game::RunGame() 
{
	//���͎�t
	input->SetInputByPlayer();

	//�I���L�[
	if (input->GetDebug()) {
		return GameStatus::Stop;
	}

	//�`�揈��
	if (!DrowGameView()) {
		return GameStatus::Stop;
	}

	float deltaTime = DeltaTime();
	//�Q�[������
	if (!PlayGame(deltaTime)) {
		return GameStatus::Stop;
	}


	return GameStatus::Play;
}

/// <summary>
/// <para>SetView</para>
/// <para>�Q�[����`�悵�܂�</para>
/// </summary>
/// <returns></returns>
bool Game::DrowGameView() 
{
	//�X�N���[���N���A
	if (!gameView->Clear()) {
		return false;
	}
	//�v���C���[�`��
	if (!player->View()) {
		return false;
	}

	return true;
}

bool Game::PlayGame(float deltaTime) 
{
	//�v���C���[�ړ�
	player->Move(input->GetInput(), deltaTime);

	return true;
}

float Game::DeltaTime() 
{
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	//�������X�V
	mTicksCount = SDL_GetTicks();

	return deltaTime;
}


/// <summary>
/// <para>Shutdown</para>
/// <para>�Q�[���̏I������</para>
/// </summary>
void Game::Shutdown() 
{
	// �Q�[���r���[�폜
	gameView->Shutdown();
}

/// <summary>
/// <para>GetGameView</para>
/// <para>�Q�[���r���[���擾���܂�</para>
/// </summary>
/// <returns>�Q�[���r���[�̃|�C���^</returns>
GameView* Game::GetGameView() 
{
	return gameView;
}
