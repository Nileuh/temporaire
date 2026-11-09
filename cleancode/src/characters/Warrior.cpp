#include "characters/Warrior.h"

#include "domain/CombatRules.h"

#include <algorithm>

Warrior::Warrior(float MaximumHealth, float Armor)
	: maximumHealth((std::max)(0.0f, MaximumHealth)),
	  health(maximumHealth),
	  armor((std::max)(0.0f, (std::min)(1.0f, Armor)))
{
}

std::string Warrior::Attack()
{
	return "Warrior attacks with a sword";
}

std::string Warrior::GetCharacterName() const
{
	return "Warrior";
}

void Warrior::TakeDamage(float RawDamage)
{
	if (health <= 0.0f)
	{
		return;
	}

	if (RawDamage <= 0.0f)
	{
		return;
	}

	health = (std::max)(0.0f, health - CombatRules::CalculateDamage(RawDamage, armor));
}

float Warrior::GetHealth() const
{
	return health;
}

float Warrior::GetArmor() const
{
	return armor;
}
