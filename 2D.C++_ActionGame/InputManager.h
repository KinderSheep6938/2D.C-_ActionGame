#pragma once
#include "GameCommon.h"

//入力向き
#define RIGHT = 1
#define LEFT = -1

/// <summary>
/// <para>Input</para>
/// <para>プレイヤー入力を管理します</para>
/// </summary>
class Input {
public:
	Input();
	//プレイヤー入力取得
	void SetInputByPlayer();
	//入力データ取得
	Vector2 GetInput();
	//デバックキー取得
	bool GetDebug();

private:
	//移動入力
	Vector2 inputVal;
	//でバックキー
	bool shutdown;

};