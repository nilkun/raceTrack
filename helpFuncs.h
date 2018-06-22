#ifndef __HELPFUNCS__
#define __HELPFUNCS__
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

void drawCircle(SDL_Renderer *renderer);
void drawCircleAdv(SDL_Renderer *renderer, int radiusInPixels);

struct DegreeCalculator {
  DegreeCalculator();
  float calculate[360][2];
  float getDegrees(int degrees, int XorY);
};

#endif
