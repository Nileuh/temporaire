#pragma once

#include "domain/ICharacter.h"

class Warrior final : public ICharacter
{
public:
	explicit Warrior(float MaximumHealth = 100.0f, float Armor = 0.25f);

	std::string Attack() override;
	std::string GetCharacterName() const override;
	void TakeDamage(float RawDamage) override;
	float GetHealth() const override;
	float GetArmor() const;

private:
	float maximumHealth;
	float health;
	float armor;
};
