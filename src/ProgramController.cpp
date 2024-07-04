#include "../include/ProgramController.h"
#include <SDL2/SDL_video.h>
#include <iostream>

ProgramController::ProgramController ()
    : _window (nullptr), _window_title ("DOOM"), _window_width (640),
      _window_height (400)

{
}

void
ProgramController::initSystems ()
{
  // Initialize SDL
  if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
      std::cout << "Failed to initialize the SDL2 library";
    }
  std::cout << "width: " << _window_width << '\n';
  std::cout << "height: " << _window_height << '\n';
  _window = SDL_CreateWindow (_window_title, SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, _window_width,
                              _window_height, 0);
  if (!_window)
    {
      std::cout << "Failed to create window" << '\n';
    }
};

void
ProgramController::run ()
{
  ProgramController::initSystems ();
};
