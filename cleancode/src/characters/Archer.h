#pragma once

#include "domain/ICharacter.h"
#include "domain/RangedAttackComponent.h"

#include <memory>

class Archer final : public ICharacter
{
public:
	explicit Archer(float MaximumHealth = 80.0f, int Arrows = 10, float MaxRange = 20.0f);

	std::string Attack() override;
	std::string GetCharacterName() const override;
	void TakeDamage(float RawDamage) override;
	float GetHealth() const override;
	int GetArrows() const;
	bool CanHit(float Distance) const;
	const RangedAttackComponent* GetRangedAttackComponent() const;

private:
	float health;
	int arrows;
	std::unique_ptr<RangedAttackComponent> rangedAttack;
};
