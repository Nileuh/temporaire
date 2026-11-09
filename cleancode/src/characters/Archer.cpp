#include "characters/Archer.h"

#include <algorithm>

Archer::Archer(float MaximumHealth, int Arrows, float MaxRange)
	: health((std::max)(0.0f, MaximumHealth)),
	  arrows((std::max)(0, Arrows)),
	  rangedAttack(std::make_unique<RangedAttackComponent>(MaxRange))
{
}

std::string Archer::Attack()
{
	if (arrows <= 0)
	{
		return "Archer has no arrows";
	}

	--arrows;
	return "Archer shoots an arrow";
}

std::string Archer::GetCharacterName() const
{
	return "Archer";
}

void Archer::TakeDamage(float RawDamage)
{
	if (RawDamage <= 0.0f || health <= 0.0f)
	{
		return;
	}

	health = (std::max)(0.0f, health - RawDamage);
}

float Archer::GetHealth() const
{
	return health;
}

int Archer::GetArrows() const
{
	return arrows;
}

bool Archer::CanHit(float Distance) const
{
	return rangedAttack && rangedAttack->CanHit(Distance);
}

const RangedAttackComponent* Archer::GetRangedAttackComponent() const
{
	return rangedAttack.get();
}
