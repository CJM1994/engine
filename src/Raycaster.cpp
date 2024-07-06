#include "../include/Raycaster.h"
// #include <iostream>

Raycaster::Raycaster (int pixel_width)
    : _positionX (7.0), _positionY (21.0), _directionX (-1.0),
      _directionY (0.0), _planeX (0.0), _planeY (0.7), _frame_time (0.0),
      _last_frame_time (0.0), _pixel_width (pixel_width)
{
  this->calculate_pixel_buffer ();
};

Raycaster::~Raycaster (){};

enum class WallSide
{
  HORZ,
  VERT,
};

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
      // std::cout << "camera_planeX: " << camera_planeX << '\n';

      // NOTE:
      // Use DDA Algorithm (Digital Differential Analyzer) to determine which
      // points the cast ray needs to check for collisions

      // Which grid tile of the map we are in
      int mapX = int (_positionX);
      int mapY = int (_positionY);

      // Store length of the ray from current position next x side or y side
      double side_distX;
      double side_distY;

      // Length of ray from on x/y side to next x/y side
      double delta_distX;
      double delta_distY;

      // Which direction to move on x or y axis (+1 or -1)
      int stepX;
      int stepY;

      bool hit{ false }; // Was a wall hit
      WallSide side;     // Was a horizontal wall hit or vertical
    }
};
