#include "../include/ProgramController.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>

int
main (int argc, char *argv[])
{
  ProgramController program_controller;
  program_controller.run ();

  return EXIT_SUCCESS;
}
