#ifndef PROGRAM_CONTROLLER
#define PROGRAM_CONTROLLER

#include <SDL2/SDL.h>

enum class ProgramState
{
  RUN,
  HALT
};

class ProgramController
{
public:
  void run ();

private:
  void init ();

  int _window_width;
  int _window_height;
  SDL_Window *_window;
  ProgramState _program_state;
};

#endif
