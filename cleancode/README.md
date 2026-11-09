# Clean Code & Clean Architecture C++17 - Correction

Version corrigée du TP de 1h30, sans Unreal Engine. Le projet utilise CMake et
doctest inclus localement; aucune dependance a telecharger n'est requise pour compiler.
La copie de doctest est la version 2.4.11, distribuee sous sa licence MIT dans
`tests/doctest-LICENSE.txt`.

## Organisation des sources

```text
src/
  domain/       # Contrats et regles metier independants
  characters/   # Implementations Warrior, Archer et Mage
  factory/      # Creation polymorphique des personnages
  application/  # Orchestration des tours de jeu
tests/           # Tests d'acceptation doctest
```

## Prerequis

- Compilateur C++17 (Visual Studio 2022, GCC ou Clang)
- CMake 3.15 ou plus recent
- Git

## Compiler et lancer les tests

Depuis le dossier `starter3correction` :

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build -C Debug --output-on-failure
```

Les trois suites `Ex1`, `Ex2` et `Ex3` doivent passer.

## Avec Visual Studio

1. Ouvrir Visual Studio 2022.
2. Choisir **Fichier > Ouvrir > Dossier** et choisir `starter3correction`.
3. Visual Studio detecte le `CMakeLists.txt`; selectionner une configuration
   x64.
4. Construire la cible `character_tests`.
5. Lancer les tests avec la commande CTest ci-dessus ou la cible `RUN_TESTS`.

## Exercices

### Exercice 1 - Guard clauses et DRY

Fichiers : `src/characters/Warrior.cpp`, `src/domain/CombatRules.h`.

- Ignorer les degats nuls ou negatifs.
- Ne plus appliquer de degats a un personnage mort.
- Borner l'armure entre 0 et 1.
- Centraliser le calcul dans `CombatRules::CalculateDamage`.
- Remplacer les imbrications par des retours anticipes.

```sh
ctest --test-dir build -C Debug -R Ex1 --output-on-failure
```

### Exercice 2 - Fabrique, polymorphisme et RAII

Fichiers : `src/factory/CharacterFactory.cpp`,
`src/application/GameSystem.cpp`.

- Utiliser l'interface `ICharacter`, fournie dans `src/domain/ICharacter.h`, pour
  manipuler polymorphiquement `Warrior`, `Archer` et `Mage`.
- Dans `CharacterFactory::CreateCharacter(CharacterType)`, creer le personnage
  correspondant et retourner un `std::unique_ptr<ICharacter>`; retourner
  `nullptr` pour une valeur inconnue.
- Dans `GameSystem::RunTurn`, obtenir le personnage via la fabrique et appeler
  `Attack()` sans dependance aux classes concretes; retourner une chaine vide
  si aucun personnage n'a pu etre cree.

```sh
ctest --test-dir build -C Debug -R Ex2 --output-on-failure
```

### Exercice 3 - Composition

Fichiers : `src/domain/RangedAttackComponent.h`,
`src/characters/Archer.h/.cpp`, `src/characters/Mage.h/.cpp`.

- Valider les tirs selon la distance et la portee maximale.
- Creer un `RangedAttackComponent` pour Archer et Mage.
- Garder Warrior sans capacite a distance.

```sh
ctest --test-dir build -C Debug -R Ex3 --output-on-failure
```

Les implementations des trois exercices se trouvent dans `src/`. `Warrior`
n'inclut pas le composant de tir; Archer et Mage le possedent par composition.
