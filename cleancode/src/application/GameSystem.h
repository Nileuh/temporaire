#pragma once

#include "domain/CharacterType.h"

#include <string>

class GameSystem
{
public:
	std::string RunTurn(CharacterType Type) const;
};
