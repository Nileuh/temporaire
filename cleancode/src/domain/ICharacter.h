#pragma once

#include <string>

class ICharacter
{
public:
	virtual ~ICharacter() = default;

	virtual std::string Attack() = 0;
	virtual std::string GetCharacterName() const = 0;
	virtual void TakeDamage(float RawDamage) = 0;
	virtual float GetHealth() const = 0;
};
