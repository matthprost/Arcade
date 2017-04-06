//
// OpenGL.cpp for cpp_arcade in /home/lopez_i/cpp_arcade/OpenGL.cpp
//
// Made by Loïc Lopez
// Login   <loic.lopez@epitech.eu>
//
// Started on  jeu. mars 16 15:07:40 2017 Loïc Lopez
// Last update Thu Apr  6 18:41:48 2017 Matthias Prost
//

#include <iostream>
#include "OpenGLViewController.hpp"

static const GLfloat g_vertex_buffer_data[] = {
 -1.0f,-1.0f,-1.0f,
 -1.0f,-1.0f, 1.0f,
 -1.0f, 1.0f, 1.0f,
 1.0f, 1.0f,-1.0f,
 -1.0f,-1.0f,-1.0f,
 -1.0f, 1.0f,-1.0f,
 1.0f,-1.0f, 1.0f,
 -1.0f,-1.0f,-1.0f,
 1.0f,-1.0f,-1.0f,
 1.0f, 1.0f,-1.0f,
 1.0f,-1.0f,-1.0f,
 -1.0f,-1.0f,-1.0f,
 -1.0f,-1.0f,-1.0f,
 -1.0f, 1.0f, 1.0f,
 -1.0f, 1.0f,-1.0f,
 1.0f,-1.0f, 1.0f,
 -1.0f,-1.0f, 1.0f,
 -1.0f,-1.0f,-1.0f,
 -1.0f, 1.0f, 1.0f,
 -1.0f,-1.0f, 1.0f,
 1.0f,-1.0f, 1.0f,
 1.0f, 1.0f, 1.0f,
 1.0f,-1.0f,-1.0f,
 1.0f, 1.0f,-1.0f,
 1.0f,-1.0f,-1.0f,
 1.0f, 1.0f, 1.0f,
 1.0f,-1.0f, 1.0f,
 1.0f, 1.0f, 1.0f,
 1.0f, 1.0f,-1.0f,
 -1.0f, 1.0f,-1.0f,
 1.0f, 1.0f, 1.0f,
 -1.0f, 1.0f,-1.0f,
 -1.0f, 1.0f, 1.0f,
 1.0f, 1.0f, 1.0f,
 -1.0f, 1.0f, 1.0f,
 1.0f,-1.0f, 1.0f
};

// One color for each vertex. They were generated randomly.
static const GLfloat g_color_buffer_data[] = {
 0.583f,  0.771f,  0.014f,
 0.609f,  0.115f,  0.436f,
 0.327f,  0.483f,  0.844f,
 0.822f,  0.569f,  0.201f,
 0.435f,  0.602f,  0.223f,
 0.310f,  0.747f,  0.185f,
 0.597f,  0.770f,  0.761f,
 0.559f,  0.436f,  0.730f,
 0.359f,  0.583f,  0.152f,
 0.483f,  0.596f,  0.789f,
 0.559f,  0.861f,  0.639f,
 0.195f,  0.548f,  0.859f,
 0.014f,  0.184f,  0.576f,
 0.771f,  0.328f,  0.970f,
 0.406f,  0.615f,  0.116f,
 0.676f,  0.977f,  0.133f,
 0.971f,  0.572f,  0.833f,
 0.140f,  0.616f,  0.489f,
 0.997f,  0.513f,  0.064f,
 0.945f,  0.719f,  0.592f,
 0.543f,  0.021f,  0.978f,
 0.279f,  0.317f,  0.505f,
 0.167f,  0.620f,  0.077f,
 0.347f,  0.857f,  0.137f,
 0.055f,  0.953f,  0.042f,
 0.714f,  0.505f,  0.345f,
 0.783f,  0.290f,  0.734f,
 0.722f,  0.645f,  0.174f,
 0.302f,  0.455f,  0.848f,
 0.225f,  0.587f,  0.040f,
 0.517f,  0.713f,  0.338f,
 0.053f,  0.959f,  0.120f,
 0.393f,  0.621f,  0.362f,
 0.673f,  0.211f,  0.457f,
 0.820f,  0.883f,  0.371f,
 0.982f,  0.099f,  0.879f
};

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
  if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS)
    {

    }

  if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS)
    {

    }
  if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS)
    {

    }
  if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS)
    {

    }

  return (true);
}

void	OpenGLViewController::initScreen(std::string const &name)
{
  if (!glfwInit())
    return;

  glfwWindowHint(GLFW_SAMPLES, 4);
  this->mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  if (!(this->window = glfwCreateWindow(this->mode->width, this->mode->height, name.c_str(), NULL, NULL)))
      return (this->endScreen());
  glfwMakeContextCurrent(this->window); // Initialize GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
    {
      std::cerr << "Failed to initialize GLEW\n" << std::endl;
      return;
    }

  glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE);
  glfwPollEvents();
}

void	OpenGLViewController::displayScore(int width, std::string const &Game, std::string const &libraryName, int score)
{
  (void)Game;
  (void)libraryName;
  (void)score;
  (void)width;
}

void	OpenGLViewController::endScreen()
{
  glfwTerminate();
}

void  OpenGLViewController::refresh()
{
  glFlush();
  glfwSwapBuffers(this->window);
  glfwPollEvents();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void	OpenGLViewController::drawSquare(int width, int x, int y, Color const &color)
{
  (void)x;
  (void)y;
  (void)color;
  (void)width;
  glBegin(GL_QUADS);
  glColor3ub(0,0,255);
  glVertex2d(-0.75,-0.75);
  glVertex2d(-0.75,0.75);
  glVertex2d(0.75,0.75);
  glVertex2d(0.75,-0.75);
  glEnd();
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
