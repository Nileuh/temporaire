# Explications des corrections par exercice

Ce document explique les modifications apportées aux `TODO EXERCICE` pour
présenter les corrections et le rôle du code.

## Exercice 1 — Guard clauses et règles de combat

### `Warrior.cpp`

L’inclusion de `CombatRules.h` rend disponible la fonction de calcul des dégâts
partagée par les règles de combat.

Dans `Warrior::TakeDamage` :

- `if (health <= 0.0f) return;` : un guerrier déjà mort ne peut plus subir de
  dégâts.
- `if (RawDamage <= 0.0f) return;` : les dégâts nuls ou négatifs sont ignorés.
- `CombatRules::CalculateDamage(RawDamage, armor)` délègue le calcul des dégâts
  après armure à une fonction centralisée.
- `(std::max)(0.0f, ...)` empêche la santé de descendre sous zéro.

Ces vérifications en début de fonction sont des *guard clauses* : elles
retournent immédiatement lorsque le traitement ne doit pas continuer. Elles
remplacent les imbrications de conditions de la version initiale.

### `CombatRules.h`

- Le premier `if` renvoie `0.0f` si les dégâts sont nuls ou négatifs.
- `ClampedArmor` borne l’armure dans l’intervalle `[0, 1]` : une valeur
  négative devient `0`, et une valeur supérieure à `1` devient `1`.
- `RawDamage * (1.0f - ClampedArmor)` calcule les dégâts restants après la
  réduction due à l’armure.

La fonction étant définie dans le fichier d’en-tête avec le mot-clé `inline`,
elle peut être incluse dans plusieurs fichiers sans créer de conflit à
l’édition de liens.

## Exercice 2 — Fabrique, polymorphisme et RAII

### `CharacterFactory.cpp`

Les inclusions de `Archer.h`, `Mage.h` et `Warrior.h` permettent à la fabrique
de créer ces classes concrètes.

Dans `CharacterFactory::CreateCharacter` :

- Le `switch` sélectionne le personnage correspondant à la valeur de
  `CharacterType`.
- Chaque `std::make_unique<...>()` crée le personnage et renvoie un
  `std::unique_ptr<ICharacter>`. Le pointeur est typé selon l’interface commune,
  plutôt que selon la classe concrète.
- Le cas `default` renvoie `nullptr` lorsque la valeur reçue ne correspond à
  aucun type connu.

### `GameSystem.cpp`

Dans `GameSystem::RunTurn` :

- `CharacterFactory::CreateCharacter(Type)` demande à la fabrique de créer le
  personnage correspondant au type reçu.
- `if (!Character)` vérifie que la fabrique a bien renvoyé un personnage.
- `return {};` renvoie une chaîne vide si aucun personnage n’a été créé.
- `Character->Attack()` appelle l’attaque via l’interface `ICharacter`, sans
  que `GameSystem` ait besoin de connaître la classe concrète.

Le `std::unique_ptr` détruit automatiquement le personnage lorsque la fonction
se termine. C’est la gestion de ressources par RAII : la durée de vie de
l’objet est liée à celle de son pointeur propriétaire.

## Exercice 3 — Composition

### `RangedAttackComponent.h`

Dans `RangedAttackComponent::CanHit` :

- `Distance >= 0.0f` rejette une distance négative.
- `Distance <= maxRange` rejette une cible au-delà de la portée maximale.
- L’opérateur `&&` exige que les deux conditions soient vraies. Les bornes
  sont inclusives : une cible à distance `0` ou exactement à `maxRange` peut
  être touchée.

`GetMaxRange()` renvoie la portée configurée dans le composant.

### `Archer.cpp` et `Mage.cpp`

Dans les constructeurs de l’archer et du mage, l’initialisation
`std::make_unique<RangedAttackComponent>(MaxRange)` crée un composant de tir à
distance propre à chaque personnage et lui transmet sa portée maximale.
`std::unique_ptr` prend en charge la durée de vie du composant.

Les méthodes `CanHit` des deux personnages délèguent la validation de la
distance à `RangedAttackComponent`. Les personnages utilisent ainsi le
comportement du composant au lieu de dupliquer sa règle.

Le guerrier n’a pas ce composant : il conserve uniquement son comportement de
combat rapproché.
