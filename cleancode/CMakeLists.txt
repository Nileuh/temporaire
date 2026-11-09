cmake_minimum_required(VERSION 3.15)

project(CleanArchitectureTP VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(character_core
    src/characters/Warrior.cpp
    src/characters/Archer.cpp
    src/characters/Mage.cpp
    src/factory/CharacterFactory.cpp
    src/application/GameSystem.cpp
)
target_include_directories(character_core PUBLIC src)

add_executable(character_tests
    tests/TestMain.cpp
)
target_link_libraries(character_tests PRIVATE character_core)
target_include_directories(character_tests PRIVATE tests)

enable_testing()
add_test(NAME Ex1 COMMAND character_tests --test-suite=Ex1)
add_test(NAME Ex2 COMMAND character_tests --test-suite=Ex2)
add_test(NAME Ex3 COMMAND character_tests --test-suite=Ex3)
