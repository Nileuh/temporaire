#pragma once

#include <algorithm>

class RangedAttackComponent
{
public:
	explicit RangedAttackComponent(float MaxRange)
		: maxRange((std::max)(0.0f, MaxRange))
	{
	}

	bool CanHit(float Distance) const
	{
		return Distance >= 0.0f && Distance <= maxRange;
	}

	float GetMaxRange() const
	{
		return maxRange;
	}

private:
	float maxRange;
};
