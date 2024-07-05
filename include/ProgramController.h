#ifndef PROGRAM_CONTROLLER
#define PROGRAM_CONTROLLER

#include "Raycaster.h"
#include <SDL2/SDL.h>
#include <string>

enum class ProgramState
{
  RUN,
  HALT
};

class ProgramController
{
public:
  // Constructor/Destructor
  ProgramController ();

  // Methods
  void run ();

  // Vars

private:
  // Methods
  void init_systems ();
  void process_input ();
  void draw ();
  void fatal_error (std::string);
  void main_loop ();

  // Vars
  ProgramState _state;
  char const *_window_title;
  SDL_Window *_window;
  int _window_width;
  int _window_height;
  Raycaster _raycaster;
};

#endif
