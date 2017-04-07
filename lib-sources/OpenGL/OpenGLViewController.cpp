//
// OpenGL.cpp for cpp_arcade in /home/lopez_i/cpp_arcade/OpenGL.cpp
//
// Made by Loïc Lopez
// Login   <loic.lopez@epitech.eu>
//
// Started on  jeu. mars 16 15:07:40 2017 Loïc Lopez
// Last update Fri Apr  7 21:17:47 2017 Matthias Prost
//

#include <iostream>
#include "OpenGLViewController.hpp"

extern "C" ILibraryViewController	*loadLibrary()
{
  return (new OpenGLViewController());
}

OpenGLViewController::OpenGLViewController()
{
}

OpenGLViewController::~OpenGLViewController()
{

}

void	OpenGLViewController::drawMenu(size_t &currentGame, std::vector<std::string> const &games, bool &exit)
{
  (void)currentGame;
  (void)games;
  (void)exit;
}

bool	OpenGLViewController::getKey(arcade::CommandType *commandType, ChangeCommandType &action, bool &exit)
{
  (void)commandType;
  // Compute new orientation
  if (glfwWindowShouldClose(this->window)
      || glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(this->window, GL_TRUE);
      exit = true;
      return (false);
    }
  else if (glfwGetKey(this->window, GLFW_KEY_3) == GLFW_PRESS)
      action = ChangeCommandType::NEXT_LIBRARY;
  else if (glfwGetKey(this->window, GLFW_KEY_2) == GLFW_PRESS)
      action = ChangeCommandType::PREV_LIBRARY;
  else if (glfwGetKey(this->window, GLFW_KEY_4) == GLFW_PRESS)
      action = ChangeCommandType::PREV_GAME;
  else if (glfwGetKey(this->window, GLFW_KEY_5) == GLFW_PRESS)
      action = ChangeCommandType::NEXT_GAME;
  else if (glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS)
      *commandType = arcade::CommandType::GO_UP;
  else if (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS)
      *commandType = arcade::CommandType::GO_DOWN;
  else if (glfwGetKey(this->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
      *commandType = arcade::CommandType::GO_RIGHT;
  else if (glfwGetKey(this->window, GLFW_KEY_LEFT) == GLFW_PRESS)
      *commandType = arcade::CommandType::GO_LEFT;

  return (true);
}

char *program_path()
{
  char *path = (char *)malloc(PATH_MAX);
  if (path != NULL) {
      if (readlink("/proc/self/exe", path, PATH_MAX) == -1) {
	  free(path);
	  path = NULL;
	}
    }
  return path;
}

void	OpenGLViewController::initScreen(std::string const &name)
{
  if (!glfwInit())
    return;
  int 		nb = 1;
  char 		*lol[] = {(char *)program_path()};
  glutInit(&nb, (char **)&lol);
  this->mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  if (!(this->window = glfwCreateWindow(this->mode->width, this->mode->height, name.c_str(), NULL, NULL)))
      return (this->endScreen());
  glfwMakeContextCurrent(this->window); // Initialize GLEW
  glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE);
  glfwPollEvents();
}

void print(float x, float y, std::string str)
{
//set the position of the text in the window using the x and y coordinates
  glRasterPos2f(x,y);
//loop to display character by character
  for (unsigned int i = 0; i < str.length(); i++)
    {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str.at(i));
    }
}

void	OpenGLViewController::displayScore(int width, std::string const &Game, std::string const &libraryName, int score)
{
  print(0.25f, 0, Game);
  print(0.25f, -0.05f, libraryName);
  print(0.25f, -0.1f, "Score");
  print(0.35f, -0.1f, std::to_string(score));
  (void)width;
}

void	OpenGLViewController::endScreen()
{
  glfwTerminate();
}

void  OpenGLViewController::refresh()
{
  glfwSwapBuffers(this->window);
  glfwPollEvents();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void	OpenGLViewController::drawSquare(int width, int x, int y, Color const &color)
{
  (void)width;
  glPushMatrix();

  const Vector2f floatWindowSize((float)this->mode->width, (float)this->mode->height);
  const Vector2f floatObjectSize((float)20,(float)20);
  const Vector2f relativeObjectSize(floatObjectSize.x / floatWindowSize.x, floatObjectSize.y / floatWindowSize.y);
  const Vector2f relativeObjectPosition((x / floatWindowSize.x) * 2.0f, (y / floatWindowSize.y) * 2.0f);

  switch (color)
  {
    case Color::BLUE:
      glColor3ub(33, 150, 243);
      break;
    case Color::BLACK:
      glColor3ub(0, 0, 0);
      break;
    case Color::MAGENTA:
      glColor3ub(33, 30, 99);
      break;
    case Color::RED:
      glColor3ub(244, 67, 54);
      break;
    case Color::GREEN:
      glColor3ub(76, 175, 80);
      break;
    case Color::CYAN:
      glColor3ub(0, 188, 212);
      break;
    case Color::YELLOW:
      glColor3ub(255, 193, 7);
      break;
    case Color::WHITE:
      glColor3ub(255, 255, 255);
      break;
    case Color::SHIP:
      glColor3ub(33, 150, 243);
      break;
    case Color::ENNEMY:
      glColor3ub(244, 67, 54);
      break;
    case Color::LASER:
      glColor3ub(76, 175, 80);
      break;
    case Color::ENNEMY_LASER:
      glColor3ub(33, 30, 99);
      break;
    case Color::SNAKE_BODY:
      glColor3ub(244, 67, 54);
      break;
    case Color::SNAKE_HEAD:
      glColor3ub(33, 30, 99);
      break;
    case Color::APPLE:
      glColor3ub(76, 175, 80);
      break;
  }

  glTranslatef((relativeObjectPosition.x * floatObjectSize.x),
	       -(relativeObjectPosition.y * floatObjectSize.y), 0.0f);
  glBegin(GL_QUADS);

  glVertex2f(-relativeObjectSize.x - (floatObjectSize.x / (float)width), -relativeObjectSize.y + 0.65f);
  glVertex2f(relativeObjectSize.x - (floatObjectSize.x / (float)width),  -relativeObjectSize.y  + 0.65f);
  glVertex2f(relativeObjectSize.x - (floatObjectSize.x / (float)width),  relativeObjectSize.y  + 0.65f);
  glVertex2f(-relativeObjectSize.x - (floatObjectSize.x / (float)width), relativeObjectSize.y  + 0.65f);
  glEnd();
  glPopMatrix();
}

std::string	OpenGLViewController::getLibraryName()
{
  return ("OpenGL");
}

void  OpenGLViewController::gameOver(int score)
{
  (void)score;
}

void  OpenGLViewController::clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
