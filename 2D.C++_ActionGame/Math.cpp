#include "Math.h"
#include <time.h>

Math::Math() {}

/// <summary>
/// <para>Random</para>
/// <para>0��1�������_���Ɏ擾���܂�</para>
/// </summary>
/// <returns></returns>
int Math::Random()
{
	time_t now = time(nullptr);
	return now % 2;
}

/// <summary>
/// <para>RandomPar</para>
/// <para>0.0����0.9�܂ł̒l��0.1�Ԋu�Ń����_���Ɏ擾���܂�</para>
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