//
// GameCore.cpp for cpp_arcade in /home/lopez_i/cpp_arcade/GameCore.cpp
//
// Made by Loïc Lopez
// Login   <loic.lopez@epitech.eu>
//
// Started on  jeu. mars 16 18:01:13 2017 Loïc Lopez
// Last update jeu. mars 16 18:01:13 2017 Loïc Lopez
//

#include "GameCore.hpp"

GameCore::GameCore(const std::string &library_name) : library_name(library_name)
{
}

GameCore::GameCore(GameCore const &controller) : library_name(controller.library_name)
{
}

GameCore& GameCore::operator=(GameCore const &controller)
{
  if (this != &controller) {}
  return (*this);
}

void GameCore::GameLauncher()
{
}