#pragma once

#include <algorithm>

namespace CombatRules
{
inline float CalculateDamage(float RawDamage, float Armor)
{
	if (RawDamage <= 0.0f)
	{
		return 0.0f;
	}

	const float ClampedArmor = (std::max)(0.0f, (std::min)(1.0f, Armor));
	return RawDamage * (1.0f - ClampedArmor);
}
}
