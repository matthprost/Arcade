/*
** SolarFox.hpp for cpp_arcade in /home/lopez_i/cpp_arcade/SolarFox.hpp.hpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  jeu. mars 16 16:02:17 2017 Loïc Lopez
** Last update Thu Apr  6 17:58:35 2017 Matthias Prost
*/

#ifndef SolarFox_HPP__
# define SolarFox_HPP__

#include <iostream>
#include "../interface/IGameModel.hpp"
#include "../../include/Cencapsulation.hpp"

extern "C" IGameModel *createInstanceGame(std::string const &);

struct  shoot
{
    bool             is_ennemy;
    uint16_t         pos;
    Shoot_direction  direction;
    uint16_t         count;
    arcade::TileType type;
    shoot();
};

class SolarFox : public IGameModel
{
 private:
   bool					alreadyLaunch;
  std::string	libraryName;
  int   pos_x;
  int   pos_y;
  int   score;
  arcade::GetMap			*Map;
  arcade::Position  	_ship;
  int                 ennemy1_pos;
  int                 ennemy2_pos;
  int                 direction1;
  int                 direction2;
  SaveCommand         last_key;
  std::vector<shoot>  shoots;

 public:
  SolarFox(std::string const &libname);
  SolarFox(SolarFox const &);
  SolarFox &operator=(SolarFox const &);
  virtual ~SolarFox();

  // Methods
  virtual void setMap();
  virtual void drawMap(ILibraryViewController *libraryInstance);
  virtual ChangeCommandType	play(ILibraryViewController *library, size_t &currentGame, size_t &currentLibrary, bool &);
  virtual int  getScore();
  virtual void setScore(int);
  virtual std::string getGameName();
  virtual void  playProtocol(void);
};

void	SolarFoxAlgorithm(arcade::GetMap *Map, arcade::Position *ship, SaveCommand *last_key, std::vector<shoot> *shoots);
void  player_shoot(arcade::GetMap *map, std::vector<shoot> *shoots, arcade::Position *_ship, SaveCommand *last_key);

#endif /* SolarFox_HPP__ */
