//
// IGameCore.hpp for cpp_arcade in /home/lopez_i/cpp_arcade/IGameCore.hpp
//
// Made by Loïc Lopez
// Login   <loic.lopez@epitech.eu>
//
// Started on  jeu. mars 16 17:56:32 2017 Loïc Lopez
// Last update jeu. mars 16 17:56:32 2017 Loïc Lopez
//

#ifndef IGAMECORE_HPP__
# define IGAMECORE_HPP__

class IGameCore
{
 public:
  virtual void	GameLauncher() = 0;
  virtual ~IGameCore() {}
};

#endif /* IGAMECORE_HPP__ */