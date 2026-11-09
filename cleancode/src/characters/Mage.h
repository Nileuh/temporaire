#pragma once

#include "domain/ICharacter.h"
#include "domain/RangedAttackComponent.h"

#include <memory>

class Mage final : public ICharacter
{
public:
	explicit Mage(float MaximumHealth = 70.0f, int Mana = 100, float MaxRange = 30.0f);

	std::string Attack() override;
	std::string GetCharacterName() const override;
	void TakeDamage(float RawDamage) override;
	float GetHealth() const override;
	int GetMana() const;
	bool CanHit(float Distance) const;
	const RangedAttackComponent* GetRangedAttackComponent() const;

private:
	float health;
	int mana;
	std::unique_ptr<RangedAttackComponent> rangedAttack;
};
