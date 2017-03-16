//
// GameCore.hpp for cpp_arcade in /home/lopez_i/cpp_arcade/GameCore.hpp
//
// Made by Loïc Lopez
// Login   <loic.lopez@epitech.eu>
//
// Started on  jeu. mars 16 18:01:13 2017 Loïc Lopez
// Last update jeu. mars 16 18:01:13 2017 Loïc Lopez
//

#include <iostream>
#include "IGameCore.hpp"

#ifndef GAMECORE_HPP__
# define GAMECORE_HPP__

class GameCore : public IGameCore
{
 private:
  const std::string	library_name;
 public:
  GameCore(std::string const &);
  GameCore	&operator=(GameCore const &);
  GameCore(GameCore const &);
  ~GameCore() {}

  // methods
  virtual void	GameLauncher();
};

#endif /* GAMECORE_HPP__ */