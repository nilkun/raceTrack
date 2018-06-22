#ifndef __CAR__
#define __CAR__
#include "helpFuncs.h"

#include <SDL2/SDL.h>

class Car {

public:
  const int DEGREES = 10;
  SDL_Texture* texture;
  float x;
  float y;
  float prevX;
  float prevY;
  float speed;
  int direction;
  // enum Turn { DEFAULT, LEFT, RIGHT };
  char turn;
  SDL_Rect position;
  SDL_Point wheelAxle;
  SDL_Point sector;
  void setTexture(SDL_Texture *settexture);
  SDL_Point lastPosition;
  void init();
  void bounce();

public:

  Car();
  void update(DegreeCalculator *degrees);
  void downdate(DegreeCalculator *degrees);
  void render(SDL_Renderer *renderer);
  void turning();
  void turnback();

};




#endif
