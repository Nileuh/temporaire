#include "characters/Mage.h"

#include <algorithm>

Mage::Mage(float MaximumHealth, int Mana, float MaxRange)
	: health((std::max)(0.0f, MaximumHealth)),
	  mana((std::max)(0, Mana)),
	  rangedAttack(std::make_unique<RangedAttackComponent>(MaxRange))
{
}

std::string Mage::Attack()
{
	if (mana <= 0)
	{
		return "Mage has no mana";
	}

	--mana;
	return "Mage casts a spell";
}

std::string Mage::GetCharacterName() const
{
	return "Mage";
}

void Mage::TakeDamage(float RawDamage)
{
	if (RawDamage <= 0.0f || health <= 0.0f)
	{
		return;
	}

	health = (std::max)(0.0f, health - RawDamage);
}

float Mage::GetHealth() const
{
	return health;
}

int Mage::GetMana() const
{
	return mana;
}

bool Mage::CanHit(float Distance) const
{
	return rangedAttack && rangedAttack->CanHit(Distance);
}

const RangedAttackComponent* Mage::GetRangedAttackComponent() const
{
	return rangedAttack.get();
}
