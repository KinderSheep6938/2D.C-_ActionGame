#include "Math.h"
#include <time.h>

Math::Math() {}

/// <summary>
/// <para>Random</para>
/// <para>0‚©1‚ðƒ‰ƒ“ƒ_ƒ€‚ÉŽæ“¾‚µ‚Ü‚·</para>
/// </summary>
/// <returns></returns>
int Math::Random()
{
	time_t now = time(nullptr);
	return now % 2;
}

/// <summary>
/// <para>RandomPar</para>
/// <para>0.0‚©‚ç0.9‚Ü‚Å‚Ì’l‚ð0.1ŠÔŠu‚Åƒ‰ƒ“ƒ_ƒ€‚ÉŽæ“¾‚µ‚Ü‚·</para>
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