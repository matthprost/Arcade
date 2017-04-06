//
// snake.cpp for cpp_arcade in /home/lopez_i/cpp_arcade/snake.cpp
//
// Made by Loïc Lopez
// Login   <loic.lopez@epitech.eu>
//
// Started on  jeu. mars 16 14:52:43 2017 Loïc Lopez
// Last update Thu Apr  6 18:01:35 2017 Matthias Prost
//

#include "SolarFox.hpp"

extern "C" IGameModel *createInstanceGame(std::string const &libname)
{
  return (new SolarFox(libname));
}

static void   initShip(arcade::Position *ship, int height, int width)
{
  ship->x = (uint16_t) (width / 2);
  ship->y = (uint16_t) (height / 2) - 1;
}

SolarFox::SolarFox(std::string const &libname)
{
  int   rand1_y;
  int   rand2_y;
  this->libraryName = libname;
  this->Map = new arcade::GetMap[sizeof(arcade::GetMap)
				 + (45 * 60 * sizeof(arcade::TileType))];

  this->Map->height = 45;
  this->Map->width = 60;
  for (int i = 0; i < this->Map->height * this->Map->width; i++)
      this->Map->tile[i] = arcade::TileType::EMPTY;
  initShip(&this->_ship, this->Map->height, this->Map->width);
  this->alreadyLaunch = false;

  rand1_y = rand() % this->Map->width - 3;
  rand2_y = rand() % this->Map->width - 9;
  while (rand1_y <= 2)
    rand1_y = rand() % this->Map->width - 2;
  while (rand2_y <= 2)
    rand2_y = rand() % this->Map->width - 2;
  this->ennemy1_pos = 1 + this->Map->width * rand1_y;
  this->ennemy2_pos = 58 + this->Map->width * rand2_y;

  this->Map->tile[ennemy1_pos] = arcade::TileType::EVIL_DUDE;
  this->Map->tile[ennemy2_pos] = arcade::TileType::EVIL_DUDE;
  this->direction1 = 0;
  this->direction2 = 0;
  this->score = 0;
  this->last_key = SaveCommand::LEFT;
}

SolarFox::SolarFox(SolarFox const &SolarFox)
{
  this->libraryName = SolarFox.libraryName;
  this->last_key = SaveCommand::LEFT;
  this->score = 0;
}

SolarFox &SolarFox::operator=(SolarFox const &SolarFox)
{
  if (this != &SolarFox)
    this->libraryName = SolarFox.libraryName;
  return (*this);
}

shoot::shoot()
{
  this->type = arcade::TileType::EMPTY;
}

SolarFox::~SolarFox()
{

}

void SolarFox::drawMap(ILibraryViewController *libraryInstance)
{
  int   i;
  int   size = this->Map->height * this->Map->width;

  i = -1;
  while (++i < size)
    {
      if (this->Map->tile[i] == arcade::TileType::BLOCK && (i % this->Map->width == 1 || i / this->Map->width == 1
          || i % this->Map->width == this->Map->width - 2
          || i / this->Map->width == this->Map->height - 2) && i / this->Map->width != 0
        && i / this->Map->width != Map->height - 1 && i % this->Map->width != 0 && i % this->Map->width != Map->width - 1)
	       libraryInstance->drawSquare(this->Map->width, i % this->Map->width,
           i / this->Map->width, Color::WHITE);
      else if (this->Map->tile[i] == arcade::TileType::BLOCK)
	       libraryInstance->drawSquare(this->Map->width, i % this->Map->width,
           i / this->Map->width, Color::CYAN);
      else if (this->Map->tile[i] == arcade::TileType::POWERUP)
     	   libraryInstance->drawSquare(this->Map->width, i % this->Map->width,
           i / this->Map->width, Color::YELLOW);
      else if (this->Map->tile[i] == arcade::TileType::EVIL_DUDE)
         libraryInstance->drawSquare(this->Map->width, i % this->Map->width,
            i / this->Map->width, Color::RED);
      else if (this->Map->tile[i] == arcade::TileType::MY_SHOOT)
         libraryInstance->drawSquare(this->Map->width, i % this->Map->width,
            i / this->Map->width, Color::GREEN);
      else if (this->Map->tile[i] == arcade::TileType::EVIL_SHOOT)
         libraryInstance->drawSquare(this->Map->width, i % this->Map->width,
            i / this->Map->width, Color::MAGENTA);
      else
	       libraryInstance->drawSquare(this->Map->width, i % this->Map->width,
           i / this->Map->width, Color::BLACK);
    }
  libraryInstance->drawSquare(this->Map->width, this->_ship.x, this->_ship.y, Color::BLUE);
}

void SolarFox::setMap()
{
  int   			i;
  int 			size = this->Map->width * this->Map->height;

  i = -1;
  while (++i < size)
  {
    if ((((i % this->Map->width) % 2 == 0 && (i / this->Map->width) % 2 == 0
          && i % this->Map->width > 12 && i % this->Map->width < 20
          && i / this->Map->width > 10 && i / this->Map->width < 35)
          || ((i % this->Map->width) % 2 == 0 && (i / this->Map->width) % 2 == 0
          && i % this->Map->width > 40 && i % this->Map->width < 48
          && i / this->Map->width > 10 && i / this->Map->width < 35))
          || (((i % this->Map->width) % 2 == 0 && (i / this->Map->width) % 2 == 0
          && i % this->Map->width > 15 && i % this->Map->width < 45
          && i / this->Map->width > 8 && i / this->Map->width < 15)
          || ((i % this->Map->width) % 2 == 0 && (i / this->Map->width) % 2 == 0
          && i % this->Map->width > 15 && i % this->Map->width < 45
          && i / this->Map->width > 30 && i / this->Map->width < 38)))
      this->Map->tile[i] = arcade::TileType::POWERUP;
    i++;
  }
  i = -1;
  while (++i < size)
    {
      if (i % this->Map->width == 0 || i / this->Map->width == 0
          || i % this->Map->width == this->Map->width - 1
          || i / this->Map->width == this->Map->height - 1)
        this->Map->tile[i] = arcade::TileType::BLOCK;
      if (i % this->Map->width == 1 || i / this->Map->width == 1
          || i % this->Map->width == this->Map->width - 2
          || i / this->Map->width == this->Map->height - 2)
        this->Map->tile[i] = arcade::TileType::BLOCK;
    }
}

void Play()
{

}

static int  verif(arcade::GetMap *map)
{
  int   i;

  i = -1;
  while (++i != map->width * map->height)
    if (map->tile[i] == arcade::TileType::POWERUP)
      return (1);
  return (0);
}

void  player_shoot(arcade::GetMap *map, std::vector<shoot> *shoots, arcade::Position *_ship, SaveCommand *last_key)
{
  shoot tmp_shoot;

  tmp_shoot.is_ennemy = false;
  tmp_shoot.count = 0;
  tmp_shoot.pos = _ship->x + map->width * _ship->y;
  tmp_shoot.direction = static_cast<Shoot_direction>(*last_key);
  map->tile[tmp_shoot.pos] = arcade::TileType::MY_SHOOT;
  shoots->push_back(tmp_shoot);
}

static void  refresh_shoot(SolarFox *solarfox, arcade::GetMap *map, std::vector<shoot> *shoots)
{
  size_t   i;
  int   x;
  int   y;

  i = -1;
  while (++i < shoots->size())
  {
    x = shoots->at(i).pos % map->width;
    y = shoots->at(i).pos / map->width;

    if (shoots->at(i).type != arcade::TileType::EVIL_SHOOT
    && shoots->at(i).type != arcade::TileType::EVIL_DUDE
    && shoots->at(i).type != arcade::TileType::MY_SHOOT
    && shoots->at(i).is_ennemy == true)
      map->tile[shoots->at(i).pos] = shoots->at(i).type;
    else
      map->tile[shoots->at(i).pos] = arcade::TileType::EMPTY;
    if (shoots->at(i).count == 5 && shoots->at(i).is_ennemy == false)
    {
      shoots->erase(shoots->begin() + i);
      break;
    }
    if (x >= map->width - 3 || x <= 2)
    {
      shoots->erase(shoots->begin() + i);
      break;
    }
    if ((y >= map->height - 3 || y <= 2) && shoots->at(i).is_ennemy == false)
    {
      shoots->erase(shoots->begin() + i);
      break;
    }
    if (shoots->at(i).direction == Shoot_direction::UP)
      y--;
    else if (shoots->at(i).direction == Shoot_direction::DOWN)
      y++;
    else if (shoots->at(i).direction == Shoot_direction::LEFT)
      x--;
    else if (shoots->at(i).direction == Shoot_direction::RIGHT)
      x++;
    shoots->at(i).count++;
    shoots->at(i).pos = x + map->width * y;
    shoots->at(i).type = map->tile[shoots->at(i).pos];
    if (map->tile[shoots->at(i).pos] == arcade::TileType::POWERUP && shoots->at(i).is_ennemy == false)
      {
        map->tile[shoots->at(i).pos] = arcade::TileType::EMPTY;
        solarfox->setScore(100);
        shoots->erase(shoots->begin() + i);
        break;
      }
    if (shoots->at(i).is_ennemy == false)
      map->tile[shoots->at(i).pos] = arcade::TileType::MY_SHOOT;
    if (shoots->at(i).is_ennemy == true)
      map->tile[shoots->at(i).pos] = arcade::TileType::EVIL_SHOOT;
  }
}

static void  Ennemy2_shoot(arcade::GetMap *map, std::vector<shoot> *shoots, int ennemy2_pos)
{
  shoot tmp_shoot2;

  tmp_shoot2.is_ennemy = true;
  tmp_shoot2.count = 0;
  tmp_shoot2.pos = (ennemy2_pos % map->width) - 2 + map->width * (ennemy2_pos / map->width);
  tmp_shoot2.direction = Shoot_direction::LEFT;
  map->tile[tmp_shoot2.pos] = arcade::TileType::EVIL_SHOOT;
  shoots->push_back(tmp_shoot2);
}

static void  Ennemy1_shoot(arcade::GetMap *map, std::vector<shoot> *shoots, int ennemy1_pos)
{
  shoot tmp_shoot;

  tmp_shoot.is_ennemy = true;
  tmp_shoot.count = 0;
  tmp_shoot.pos = (ennemy1_pos % map->width) + 2 + map->width * (ennemy1_pos / map->width);
  tmp_shoot.direction = Shoot_direction::RIGHT;
  map->tile[tmp_shoot.pos] = arcade::TileType::EVIL_SHOOT;
  shoots->push_back(tmp_shoot);
}

static void  Ennemy(int &ennemy1_pos, int &ennemy2_pos, arcade::GetMap *map, int &direction1, int &direction2)
{
  int x;
  int y;
  int i;

  map->tile[ennemy2_pos] = arcade::TileType::BLOCK;
  map->tile[ennemy1_pos] = arcade::TileType::BLOCK;

  x = ennemy1_pos % map->width;
  y = ennemy1_pos / map->width;
  if (y >= map->height - 3)
    direction1 = -1;
  else if (y <= 2)
    direction1 = 0;
  if (direction1 == 0)
    y++;
  else if (direction1 == -1)
    y--;
  i = x + map->width * y;
  ennemy1_pos = i;
  map->tile[ennemy1_pos] = arcade::TileType::EVIL_DUDE;

  x = ennemy2_pos % map->width;
  y = ennemy2_pos / map->width;
  if (y >= map->height - 3)
    direction2 = -1;
  else if (y <= 2)
    direction2 = 0;
  if (direction2 == 0)
    y++;
  else if (direction2 == -1)
    y--;
  i = x + map->width * y;
  ennemy2_pos = i;
  map->tile[ennemy2_pos] = arcade::TileType::EVIL_DUDE;
}

static	bool	Ship_collision(std::vector<shoot> *shoots, arcade::GetMap *map, uint16_t pos_x,
					      uint16_t pos_y)
{
  int   			i;
  int         j;
  size_t      e;
  int 			lenght = map->width * map->height;

  i = -1;
  j = pos_x + map->width * pos_y;
  if (map->type == arcade::CommandType::PLAY)
    return (false);
  while (++i < lenght)
    {
      if ((map->tile[i] == arcade::TileType::BLOCK && pos_x == 1) ||
       (map->tile[i] == arcade::TileType::BLOCK && pos_y == 1) ||
       (map->tile[i] == arcade::TileType::BLOCK && pos_y == map->height - 2) ||
       (map->tile[i] == arcade::TileType::BLOCK && pos_x == map->width - 2))
	      return (true);
    }
    (void)shoots;
  e = -1;
  while (++e < shoots->size())
  {
    if (shoots->at(e).pos == j && shoots->at(e).is_ennemy == true)
      return (true);
  }
  return (false);
}

int         SolarFox::getScore()
{
  return (this->score);
}

void         SolarFox::setScore(int value)
{
  this->score += value;
}

static void resetMap(arcade::GetMap *Map)
{
  int   			i;
  int 			size = Map->width * Map->height;

  i = -1;
  while (++i < size)
    Map->tile[i] = arcade::TileType::EMPTY;
  i = -1;
  while (++i < size)
  {
    if ((((i % Map->width) % 2 == 0 && (i / Map->width) % 2 == 0
          && i % Map->width > 12 && i % Map->width < 20
          && i / Map->width > 10 && i / Map->width < 35)
          || ((i % Map->width) % 2 == 0 && (i / Map->width) % 2 == 0
          && i % Map->width > 40 && i % Map->width < 48
          && i / Map->width > 10 && i / Map->width < 35))
          || (((i % Map->width) % 2 == 0 && (i / Map->width) % 2 == 0
          && i % Map->width > 15 && i % Map->width < 45
          && i / Map->width > 8 && i / Map->width < 15)
          || ((i % Map->width) % 2 == 0 && (i / Map->width) % 2 == 0
          && i % Map->width > 15 && i % Map->width < 45
          && i / Map->width > 30 && i / Map->width < 38)))
      Map->tile[i] = arcade::TileType::POWERUP;
    i++;
  }
  i = -1;
  while (++i < size)
    {
      if (i % Map->width == 0 || i / Map->width == 0
          || i % Map->width == Map->width - 1
          || i / Map->width == Map->height - 1)
        Map->tile[i] = arcade::TileType::BLOCK;
      else if (i % Map->width == 1 || i / Map->width == 1
          || i % Map->width == Map->width - 2
          || i / Map->width == Map->height - 2)
        Map->tile[i] = arcade::TileType::BLOCK;
    }
}

static void	restartSolarFox(arcade::Position *_ship,
				ILibraryViewController *libraryInstance,
				arcade::GetMap *Map, std::vector<shoot> *shoots,
        int *ennemy1_pos, int *ennemy2_pos)
{
  libraryInstance->clear();
  shoots->clear();
  initShip(_ship, Map->height, Map->width);
  resetMap(Map);
  *ennemy1_pos = 1 + Map->width * 2;
  *ennemy2_pos = 58 + Map->width * 42;
  Map->type = arcade::CommandType::PLAY;
}

ChangeCommandType	SolarFox::play(ILibraryViewController *libraryInstance,
			       size_t &currentGame, size_t & currentLibrary,
			       bool &exit)
{
  ChangeCommandType action = ChangeCommandType::STANDBY;
  this->Map->type = arcade::CommandType::PLAY;
  std::chrono::time_point<std::chrono::system_clock> start, end;
  std::chrono::time_point<std::chrono::system_clock> ennemy1_start, ennemy1_end;
  std::chrono::time_point<std::chrono::system_clock> ennemy2_start, ennemy2_end;
  long long int elapsed_milliseconds;
  long long int ennemy1_milliseconds;
  long long int ennemy2_milliseconds;

  start = std::chrono::system_clock::now();
  ennemy1_start = std::chrono::system_clock::now();
  ennemy2_start = std::chrono::system_clock::now();
  if (!this->alreadyLaunch)
    {
      libraryInstance->initScreen(this->getGameName());
      this->setMap();
      this->alreadyLaunch = true;
    }
  while (libraryInstance->getKey(&this->Map->type, action, exit))
  {
    end = std::chrono::system_clock::now();
    ennemy1_end = std::chrono::system_clock::now();
    ennemy2_end = std::chrono::system_clock::now();
    elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    ennemy1_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(ennemy1_end - ennemy1_start).count();
    ennemy2_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(ennemy2_end - ennemy2_start).count();
    if (this->Map->type == arcade::CommandType::RESTART)
     this->Map->type = (arcade::CommandType)this->last_key;
    this->drawMap(libraryInstance);
    if (Ship_collision(&this->shoots, this->Map, this->_ship.x, this->_ship.y))
    {
      restartSolarFox(&this->_ship, libraryInstance, this->Map, &this->shoots,
                      &this->ennemy1_pos, &this->ennemy2_pos);
    }
    if (this->Map->type == arcade::CommandType::RESTART)
      {
        this->alreadyLaunch = true;
        this->score = 0;
        action = ChangeCommandType::RESTART;
        return (action);
      }
      if (this->Map->type != arcade::CommandType::PLAY && ennemy1_milliseconds > 1685)
      {
        Ennemy1_shoot(this->Map, &this->shoots, this->ennemy1_pos);
        ennemy1_start = ennemy1_end;
      }
      if (this->Map->type != arcade::CommandType::PLAY && ennemy2_milliseconds > 1280)
      {
        Ennemy2_shoot(this->Map, &this->shoots, this->ennemy2_pos);
        ennemy2_start = ennemy2_end;
      }
      if (this->Map->type != arcade::CommandType::PLAY && elapsed_milliseconds > 68)
        refresh_shoot(this, this->Map, &this->shoots);
      if (this->Map->type != arcade::CommandType::PLAY && elapsed_milliseconds > 78)
      {
        SolarFoxAlgorithm(this->Map, &this->_ship, &this->last_key, &this->shoots);
        Ennemy(this->ennemy1_pos, this->ennemy2_pos, this->Map, this->direction1, this->direction2);
        start = end;
      }
    if (action == ChangeCommandType::NEXT_LIBRARY)
      {
        currentLibrary++;
        this->alreadyLaunch = false;
        break;
      }
    else if (action == ChangeCommandType::PREV_LIBRARY)
      {
        currentLibrary--;
        this->alreadyLaunch = false;
        break;
      }
    else if (action == ChangeCommandType::PREV_GAME)
      {
        currentGame--;
        break;
      }
    else if (action == ChangeCommandType::NEXT_GAME)
      {
        currentGame++;
        break;
      }
    if (verif(this->Map) == 0)
      break;
    libraryInstance->displayScore(this->Map->width, this->getGameName(),
				libraryInstance->getLibraryName(), this->score);
    libraryInstance->refresh();
  }
  libraryInstance->endScreen();
  return (action);
}

std::string	SolarFox::getGameName()
{
  return ("SolarFox");
}

void  SolarFox::playProtocol()
{

}
