#include "Game.h"

#define START_POS_X (WIN_H / HALF)
#define START_POS_Y 74.9

/// <summary>
/// <para>Game</para>
/// <para>�R���X�g���N�^</para>
/// </summary>
Game::Game()
{
	// �\���֘A
	gameView = new GameView();

	// �}�b�v�֘A
	map = new Map(gameView);
	collManager = new ColliderManager(map->GetBlockListPtr(),map->GetLength());

	// �v���C���[�֘A
	input = new Input();
	Vector2 sPos = Vector2(WIN_W_CENTOR, WIN_H_CENTOR);
	Vector2 sSize = VECTOR_ONE;
	player = new Player(&sPos, &sSize, gameView, collManager);

	// �A�E�g�v�b�g
	camera = new Camera(player, map->GetBlockListPtr());

	mTicksCount = SDL_GetTicks();
	needRender = true;
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

	//�`�揈��
	if (!DrowGameView()) {
		return GameStatus::Stop;
	}
	
	return init;
}

/// <summary>
/// <para>RunGame</para>
/// <para>�Q�[���̃v���C����</para>
/// </summary>
GameStatus Game::RunGame() 
{
	//60FPS�ҋ@
	if (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16)) {
		return GameStatus::Play;
	}

	float deltaTime = DeltaTime();
	//���͎�t
	input->SetInputByPlayer();

	//�I���L�[
	if (input->GetDebug()) {
		return GameStatus::Stop;
	}

	//�Q�[������
	if (!PlayGame(deltaTime)) {
		return GameStatus::Stop;
	}

	if (!Output()) {
		return GameStatus::Stop;
	}

	//�`�揈��
	if (!DrowGameView()) {
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
	//�`��X�V�m�F
	if (!needRender) {
		return true;
	}

	// �X�N���[���N���A
	if (!gameView->Clear(map->GetHeight())) {
		return false;
	}

	// �v���C���[�`��
	if (!player->View()) {
		return false;
	}

	// �}�b�v�`��
	if (!map->View()) {
		return false;
	}

	gameView->DrowText(0);

	gameView->Update();

	return true;
}

/// <summary>
/// <para>PlayGame</para>
/// <para>�Q�[���̃v���C�������s���܂�</para>
/// </summary>
/// <param name="deltaTime"></param>
/// <returns></returns>
bool Game::PlayGame(float deltaTime) 
{
	// ���͎擾
	Vector2* set = input->GetInput();

	// �v���C���[���f
	player->Move(set, deltaTime);

	return true;
}

/// <summary>
/// <para>Output</para>
/// <para>�Q�[���v���C���ʂ���ʂɔ��f�����܂�</para>
/// </summary>
bool Game::Output() 
{
	// �����̈ړ���
	float holizontalVal = player->GetCollider()->pos.x - WIN_W_CENTOR;
	// �c���̈ړ���
	float verticalVal = 0;
	// ���x�X�V���C���𒴂���
	if (player->GetCollider()->pos.y < WIN_H_CENTOR - OBJECT_SIZE) {
		verticalVal = player->GetCollider()->pos.y - (WIN_H_CENTOR - OBJECT_SIZE);
		// ���ݍ��x�X�V
		map->AddHeight(verticalVal);
	}

	// �X�N���[����
	Vector2 scrollVal = Vector2(-holizontalVal, -verticalVal);
	camera->Scroll(&scrollVal);

	// ��ʓ��Ƀv���C���[�����݂��Ȃ�
	if (!player->GetCollider()->ExistInScreen()) {
		return false;
	}
	return true;
}

/// <summary>
/// <para>DeltaTime</para>
/// <para>�t���[���o�ߎ���</para>
/// </summary>
/// <returns></returns>
float Game::DeltaTime() 
{
	//�O�t���[������16ms���o�߂���܂ő҂�
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	//�������X�V
	mTicksCount = SDL_GetTicks();

	//�f���^�^�C�����ő�l�Ő�������
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}

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
