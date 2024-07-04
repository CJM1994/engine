#include "../include/ProgramController.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <iostream>

int
main (int argc, char *argv[])
{
  bool keep_window_open{ true };

  ProgramController program_controller;
  program_controller.run ();

  SDL_Surface *window_surface
      = SDL_GetWindowSurface (program_controller._window);

  if (!window_surface)
    {
      std::cout << "Failed to create surface" << '\n';
      return EXIT_FAILURE;
    }

  SDL_Surface *image = SDL_LoadBMP ("build/doom.bmp");

  if (!image)
    {
      std::cout << "Failed to load image" << '\n';
      std::cout << "SDL2 Error: " << SDL_GetError () << '\n';
    }

  // Keep window open until closed
  while (keep_window_open)
    {
      // Poll for events and update on event
      SDL_Event e;
      while (SDL_PollEvent (&e) > 0)
        {
          switch (e.type)
            {
            case SDL_QUIT:
              keep_window_open = false;
              break;
            }
        }
      SDL_BlitSurface (image, NULL, window_surface, NULL);
      // Update window
      SDL_UpdateWindowSurface (program_controller._window);
    }

  return EXIT_SUCCESS;
}
