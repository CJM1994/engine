#include "../include/Raycaster.h"

Raycaster::Raycaster (int pixel_width)
    : _positionX (7.0), _positionY (21.0), _directionX (-1.0),
      _directionY (0.0), _planeX (0.0), _planeY (0.7), _frame_time (0.0),
      _last_frame_time (0.0)
{
  // Need to get screen width here
  return;
};

Raycaster::~Raycaster (){};
