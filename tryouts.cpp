
#include <cmath>
#include "tryouts.h"

void getShape(SDL_Rect &rect, SDL_Rect &x_coords, SDL_Rect &y_coords, int degrees){

//  float x_left_to_right_ratio = (rectangle.w - offset_x)/rectangle.w; // This will be between 0-1.
//  float yRatio = (rectangle.h - offset_y)/rectangle/.h; // This will be between 0-1.


  float PI = 3.14159265;
  float radians = PI * degrees / 180;
  float cosine_x = rect.w * cos(radians);
  float sine_y = rect.h * sin(radians);
  float sine_x = rect.w * sin(radians);
  float cosine_y = rect.h * cos(radians);
  //
  // SDL_Rect x_coords;
  // SDL_Rect y_coords;

  // better ratios to understand;
  // float x_multiplier = rect.w / (rect.w - offset_x);
  // float y_multiplier = rect.h / (rect.h - offset_y);

  // include top LEFT
  // int distToRight = offsetX;
  // int distUp = offsetY;

  // need hypoteneuse!!
  //float hypoteneuse = sqrt( (offsetX*offSetX) + (offsetY*offSetY) );
  //float hypDegrees =
  // float fakePositionX = rect.x + 4;
  // float fakePositionY = rect.y + 12;
  //SIMPLE SOLUTION
  //go to x point...
  // h = 4;
  // get xLoc
  float firstX = -(4 * cos(radians));
  float firstY = -(4 * sin(radians));

  float secondX = 12 * sin(radians);
  float secondY = -(12 * cos(radians));

  float current_x = 4 + secondX + firstX;
  float current_y = 12 + secondY + firstY;


  //then go to point y...
  // current_x += cosine_x * 0.5;
  // current_y += -sine_y * 0.75;

//  float current_x = distToRight * cos(radians);
//  float current_y = distUp * sin(radians);

//  current_x -= cosine_x;
//  current_y -= cosine_y;
  x_coords.x = rect.x + current_x;
  y_coords.x = rect.y + current_y;

  // move to top right
  current_x += rect.w * cos(radians);
  current_y += rect.w * sin(radians);
  x_coords.y = rect.x + current_x;
  y_coords.y = rect.y + current_y;

  //go down!
  current_x -= rect.h * sin(radians);;
  current_y += rect.h * cos(radians);;
  x_coords.w = rect.x + current_x;
  y_coords.w = rect.y + current_y;

  // bottom left
  current_x -= rect.w * cos(radians);;
  current_y -= rect.w * sin(radians);;
  x_coords.h = rect.x + current_x;
  y_coords.h = rect.y + current_y;
}
