#include "../include/ProgramController.h"
#include "../include/Raycaster.h"
#include <GL/gl.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <iostream>

ProgramController::ProgramController ()
    : _state (ProgramState::RUN), _window_title ("PROGRAM WINDOW"),
      _window (nullptr), _window_width (640), _window_height (480),
      _raycaster (_window_width, _window_height)
{
}

void
ProgramController::init_systems ()
{
  // SDL
  if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
      fatal_error ("Failed to initialize the SDL2 library");
    }
  _window = SDL_CreateWindow (_window_title, SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, _window_width,
                              _window_height, SDL_WINDOW_OPENGL);
  if (_window == nullptr)
    {
      fatal_error ("Failed to create window with SDL2");
    }
  // OpenGL
  SDL_GLContext const gl_context{ SDL_GL_CreateContext (_window) };
  if (gl_context == nullptr)
    {
      fatal_error ("Failed to create SDL_GLContext");
    }

  // Basic OpenGL configuration
  SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, true); // Double Buffering Mode
  glClearColor (0, 0, 255, 255);                   // Opaque Blue Background

  // Set up orthographic view for displaying textured quad
  glViewport (0, 0, _window_width, _window_height);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glOrtho (0.0, _window_width, 0.0, _window_height, -1.0, 1.0);
};

void
ProgramController::process_input ()
{
  SDL_Event e;
  while (SDL_PollEvent (&e) > 0)
    {
      switch (e.type)
        {
        case SDL_QUIT:
          _state = ProgramState::HALT;
        case SDL_KEYDOWN:
          std::cout << "key pressed: " << e.key.keysym.scancode << '\n';
          break;
        }
    }
}

void
ProgramController::draw ()
{
  // Clear
  glClear (GL_COLOR_BUFFER_BIT);

  // Render a textured quad
  glBegin (GL_QUADS);

  // Bottom-Left
  glTexCoord2f (0.0f, 0.0f);
  glVertex2i (0, 0);

  // Bottom-Right
  glTexCoord2f (1.0f, 0.0f);
  glVertex2i (_window_width, 0);

  // Top-Right
  glTexCoord2f (1.0f, 1.0f);
  glVertex2i (_window_width, _window_height);

  // Top-Left
  glTexCoord2f (0.0f, 1.0f);
  glVertex2i (0, _window_height);

  glEnd ();

  // Swap buffers
  SDL_GL_SwapWindow (_window);
}

void
ProgramController::fatal_error (std::string error)
{
  std::cout << error << '\n';
  if (SDL_GetError ())
    {
      std::cout << "Last SDL2 error: " << SDL_GetError () << '\n';
    }
  std::cout << "Fatal error, enter any string to close the application"
            << '\n';
  char input;
  std::cin >> input;
  SDL_Quit ();
  exit (EXIT_FAILURE);
}

void
ProgramController::main_loop ()
{
  // Keep window open until closed
  while (_state == ProgramState::RUN)
    {
      // Poll for events and update on event
      process_input ();
      // Update window
      draw ();
    }
}

void
ProgramController::run ()
{
  ProgramController::init_systems ();
  ProgramController::main_loop ();
};
