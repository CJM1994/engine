#include "../include/ProgramController.h"
#include <SDL2/SDL_video.h>
#include <iostream>

ProgramController::ProgramController ()
    : _state (ProgramState::RUN), _window_title ("DOOM"), _window (nullptr),
      _window_width (640), _window_height (400)

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

  SDL_Surface *window_surface = SDL_GetWindowSurface (_window);

  if (!window_surface)
    {
      std::cout << "Failed to create surface" << '\n';
    }

  SDL_Surface *image = SDL_LoadBMP ("assets/doom.bmp");

  if (!image)
    {
      std::cout << "Failed to load image" << '\n';
      std::cout << "SDL2 Error: " << SDL_GetError () << '\n';
    }

  // Keep window open until closed
  while (_state == ProgramState::RUN)
    {
      // Poll for events and update on event
      SDL_Event e;
      while (SDL_PollEvent (&e) > 0)
        {
          switch (e.type)
            {
            case SDL_QUIT:
              _state = ProgramState::HALT;
              break;
            }
        }
      // Update window
      SDL_BlitSurface (image, NULL, window_surface, NULL);
      SDL_UpdateWindowSurface (_window);
    }
};

void
ProgramController::run ()
{
  ProgramController::initSystems ();
};
