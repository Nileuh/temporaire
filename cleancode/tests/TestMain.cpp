#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "characters/Archer.h"
#include "factory/CharacterFactory.h"
#include "domain/CombatRules.h"
#include "application/GameSystem.h"
#include "characters/Mage.h"
#include "domain/RangedAttackComponent.h"
#include "characters/Warrior.h"

#include <memory>
#include <type_traits>
#include <utility>

namespace
{
template <typename T, typename = void>
struct HasRangedAttackAccessor : std::false_type
{
};

template <typename T>
struct HasRangedAttackAccessor<T, std::void_t<decltype(std::declval<const T&>().GetRangedAttackComponent())>>
	: std::true_type
{
};
}

TEST_CASE("Exercise1_CleanCodeAndGuardClauses" * doctest::test_suite("Ex1"))
{
	SUBCASE("damage formula clamps armor and ignores non-positive damage")
	{
		CHECK(CombatRules::CalculateDamage(100.0f, 0.4f) == doctest::Approx(60.0f));
		CHECK(CombatRules::CalculateDamage(100.0f, 2.0f) == doctest::Approx(0.0f));
		CHECK(CombatRules::CalculateDamage(-10.0f, 0.4f) == doctest::Approx(0.0f));
	}

	SUBCASE("warrior ignores invalid damage and damage after death")
	{
		Warrior warrior(100.0f, 0.4f);
		warrior.TakeDamage(-10.0f);
		CHECK(warrior.GetHealth() == doctest::Approx(100.0f));

		warrior.TakeDamage(100.0f);
		CHECK(warrior.GetHealth() == doctest::Approx(40.0f));
		warrior.TakeDamage(1000.0f);
		CHECK(warrior.GetHealth() == doctest::Approx(0.0f));
		warrior.TakeDamage(20.0f);
		CHECK(warrior.GetHealth() == doctest::Approx(0.0f));
	}
}

TEST_CASE("Exercise2_FactoryAndPolymorphism" * doctest::test_suite("Ex2"))
{
	SUBCASE("factory creates all concrete character types with RAII")
	{
		std::unique_ptr<ICharacter> warrior = CharacterFactory::CreateCharacter(CharacterType::Warrior);
		std::unique_ptr<ICharacter> archer = CharacterFactory::CreateCharacter(CharacterType::Archer);
		std::unique_ptr<ICharacter> mage = CharacterFactory::CreateCharacter(CharacterType::Mage);

		REQUIRE(warrior != nullptr);
		REQUIRE(archer != nullptr);
		REQUIRE(mage != nullptr);
		CHECK(warrior->GetCharacterName() == "Warrior");
		CHECK(archer->GetCharacterName() == "Archer");
		CHECK(mage->GetCharacterName() == "Mage");
		CHECK(dynamic_cast<Warrior*>(warrior.get()) != nullptr);
		CHECK(dynamic_cast<Archer*>(archer.get()) != nullptr);
		CHECK(dynamic_cast<Mage*>(mage.get()) != nullptr);
	}

	SUBCASE("game system uses the interface and handles unknown types")
	{
		GameSystem game;
		CHECK(game.RunTurn(CharacterType::Warrior) == "Warrior attacks with a sword");
		CHECK(game.RunTurn(CharacterType::Archer) == "Archer shoots an arrow");
		CHECK(game.RunTurn(CharacterType::Mage) == "Mage casts a spell");
		CHECK(game.RunTurn(static_cast<CharacterType>(255)).empty());
	}
}

TEST_CASE("Exercise3_Composition" * doctest::test_suite("Ex3"))
{
	SUBCASE("ranged component validates inclusive range and invalid distances")
	{
		RangedAttackComponent ranged(20.0f);
		CHECK(ranged.CanHit(20.0f));
		CHECK(ranged.CanHit(10.0f));
		CHECK_FALSE(ranged.CanHit(20.1f));
		CHECK_FALSE(ranged.CanHit(-1.0f));
	}

	SUBCASE("archer and mage compose ranged capability but warrior does not")
	{
		Archer archer;
		Mage mage;
		Warrior warrior;

		CHECK(archer.GetRangedAttackComponent() != nullptr);
		CHECK(mage.GetRangedAttackComponent() != nullptr);
		CHECK(archer.CanHit(20.0f));
		CHECK(mage.CanHit(30.0f));
		CHECK_FALSE(HasRangedAttackAccessor<Warrior>::value);
		CHECK(warrior.GetCharacterName() == "Warrior");
	}
}
