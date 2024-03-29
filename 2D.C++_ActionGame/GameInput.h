#pragma once
#include "GameCommon.h"

//移動量
#define BIG_JUMP 1100
#define SMALL_JUMP 650

/// <summary>
/// <para>Input</para>
/// <para>プレイヤー入力を管理します</para>
/// </summary>
class Input 
{
public:
	Input();
	// プレイヤー入力取得
	void SetInputByPlayer();
	// 入力データ取得
	Vector2* GetInput();
	// デバックキー取得
	bool GetDebug();

private:
	// 移動入力
	Vector2 inputVal;
	// でバックキー
	bool shutdown;

};