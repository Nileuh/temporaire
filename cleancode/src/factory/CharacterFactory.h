#pragma once

#include "domain/CharacterType.h"
#include "domain/ICharacter.h"

#include <memory>

class CharacterFactory
{
public:
	static std::unique_ptr<ICharacter> CreateCharacter(CharacterType Type);
};
