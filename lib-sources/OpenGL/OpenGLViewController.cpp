//
// OpenGL.cpp for cpp_arcade in /home/lopez_i/cpp_arcade/OpenGL.cpp
//
// Made by Loïc Lopez
// Login   <loic.lopez@epitech.eu>
//
// Started on  jeu. mars 16 15:07:40 2017 Loïc Lopez
// Last update Tue Mar 21 20:20:22 2017 Matthias Prost
//

#include "OpenGLViewController.hpp"
#include <GL/gl.h>

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

void	OpenGLViewController::drawMenu()
{
}

void	OpenGLViewController::drawCharacter(std::array<int, 2> &position)
{
  (void)position;
}

void	OpenGLViewController::drawMap(std::map<int, int> &map)
{
  (void)map;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  (void)scancode;
  (void)mods;
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

// Changer et enlever la boucle pour intégrer aux jeux
void	OpenGLViewController::initScreen()
{
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
    return;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return;
    }

  glfwMakeContextCurrent(window);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
    {
      /* Render here */
      glClear(GL_COLOR_BUFFER_BIT);
      glfwSetKeyCallback(window, key_callback);
      /* Swap front and back buffers */
      glfwSwapBuffers(window);

      /* Poll for and process events */
      glfwPollEvents();
    }

  glfwTerminate();
}