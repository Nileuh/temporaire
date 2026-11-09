#include "application/GameSystem.h"

#include "factory/CharacterFactory.h"
#include <memory>

std::string GameSystem::RunTurn(CharacterType Type) const
{
	std::unique_ptr<ICharacter> Character = CharacterFactory::CreateCharacter(Type);
	if (!Character)
	{
		return {};
	}

	return Character->Attack();
}
