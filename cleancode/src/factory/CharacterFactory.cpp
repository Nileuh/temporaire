#include "factory/CharacterFactory.h"

#include "characters/Archer.h"
#include "characters/Mage.h"
#include "characters/Warrior.h"

std::unique_ptr<ICharacter> CharacterFactory::CreateCharacter(CharacterType Type)
{
	switch (Type)
	{
	case CharacterType::Warrior:
		return std::make_unique<Warrior>();
	case CharacterType::Archer:
		return std::make_unique<Archer>();
	case CharacterType::Mage:
		return std::make_unique<Mage>();
	default:
		return nullptr;
	}
}
