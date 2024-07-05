#include "../include/Raycaster.h"
#include <iostream>

Raycaster::Raycaster (int pixel_width)
    : _positionX (7.0), _positionY (21.0), _directionX (-1.0),
      _directionY (0.0), _planeX (0.0), _planeY (0.7), _frame_time (0.0),
      _last_frame_time (0.0), _pixel_width (pixel_width)
{
  this->calculate_pixel_buffer ();
};

Raycaster::~Raycaster (){};

void
Raycaster::calculate_pixel_buffer ()
{
  // Scan from left side of view to right side, by columns 1 pixel wide
  for (int current_pixel{ 0 }; current_pixel < _pixel_width; current_pixel++)
    {
      // Calculate ray direction for current pixel
      double camera_planeX = ((double (current_pixel) * 2) / _pixel_width) - 1;
      double ray_directionX = _directionX + (_planeX * camera_planeX);
      double ray_directionY = _directionY + (_planeY * camera_planeX);
      std::cout << "CameraPlaneX: " << camera_planeX << '\n';

      // Use DDA Algorithm (Digital Differential Analyzer) to determine which
      // points the cast ray needs to check for collisions
    }
};
