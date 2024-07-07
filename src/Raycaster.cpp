#include "../include/Raycaster.h"
#include <iostream>

Raycaster::Raycaster (int pixel_width, int pixel_height)
    : _positionX (13.0), _positionY (8.0), _directionX (-1.0),
      _directionY (0.0), _planeX (0.0), _planeY (0.7), _frame_time (0.0),
      _last_frame_time (0.0), _pixel_width (pixel_width),
      _pixel_height (pixel_height)
{
  this->calculate_pixel_buffer ();
};

Raycaster::~Raycaster (){};

enum class WallSide
{
  HORZ, // x side
  VERT, // y side
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
      int mapX = int (_positionX); // round down
      int mapY = int (_positionY); // round down

      // Store length of the ray from current position next x side or y side
      double side_distX;
      double side_distY;

      // Length of ray from on x/y side to next x/y side
      double delta_distX{ std::abs (1 / ray_directionX) };
      double delta_distY{ std::abs (1 / ray_directionY) };
      double perp_wall_dist; // Shortest dist from camera plane to hit point

      // Which direction to move on x or y axis (+1 or -1)
      int stepX;
      int stepY;

      bool hit{ false }; // Was a wall hit
      WallSide side;     // Was a horizontal wall hit or vertical

      // Calculate step direction and the initial side distance
      if (ray_directionX < 0)
        {
          stepX = -1;
          side_distX = (_positionX - mapX) * delta_distX;
        }
      else
        {
          stepX = 1;
          side_distX = (mapX + 1.0 - _positionX) * delta_distX;
        }
      if (ray_directionY < 0)
        {
          stepY = -1;
          side_distY = (_positionY - mapY) * delta_distY;
        }
      else
        {
          stepY = 1;
          side_distY = (mapY + 1.0 - _positionY) * delta_distY;
        }

      // Perform DDA
      while (hit == false)
        {
          // If side_distX < side_distY walk along the x axis with ray
          if (side_distX < side_distY)
            {
              mapX += stepX;             // move one cell on x axis
              side_distX += delta_distX; // get distance to next x side
              side = WallSide::VERT;
            }
          else
            {
              mapY += stepY;
              side_distY += delta_distY;
              side = WallSide::HORZ;
            }
          // Check if a wall has been hit
          if (_test_map[mapX][mapY] > 0)
            {
              hit = true;
            }
        }

      // Get distance from camera plane to ray hit
      if (side == WallSide::HORZ)
        {
          perp_wall_dist = side_distX - delta_distX;
        }
      else
        {
          perp_wall_dist = side_distY - delta_distY;
        }

      // Calculate the length of line to draw
      // Walls should be full screen height at 1 unit distance
      int line_height = _pixel_height / perp_wall_dist;

      // Calculate lowest and highest pixel to draw
      // Center of wall will always be in center of screen
      int draw_start = (_pixel_height) / 2 - (line_height) / 2;
      int draw_end = _pixel_height - draw_start;
      if (draw_start < 0)
        draw_start = 0;
      if (draw_end < _pixel_height)
        draw_end = _pixel_height--;

      // Choose colour based on map data
    }
};
