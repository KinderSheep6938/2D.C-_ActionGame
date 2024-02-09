#include "Math.h"
#include <time.h>

Math::Math() {}

/// <summary>
/// <para>Random</para>
/// <para>0か1をランダムに取得します</para>
/// </summary>
/// <returns></returns>
int Math::Random()
{
	time_t now = time(nullptr);
	return now % 2;
}

/// <summary>
/// <para>RandomPar</para>
/// <para>0.0から0.9までの値を0.1間隔でランダムに取得します</para>
/// </summary>
/// <param name="low"></param>
/// <param name="high"></param>
/// <returns></returns>
float Math::RandomPar()
{
	time_t now = time(nullptr);
	float per = now % 10 / 10;
	return per;
}