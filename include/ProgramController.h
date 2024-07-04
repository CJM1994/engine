#ifndef PROGRAM_CONTROLLER
#define PROGRAM_CONTROLLER

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
  SDL_Window *_window;

private:
  // Methods
  void initSystems ();

  // Vars
  char const *_window_title;
  int _window_width;
  int _window_height;
  ProgramState _program_state;
};

#endif
