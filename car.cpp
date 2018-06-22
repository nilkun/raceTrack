#include "car.h"

class Volvo {
public:
  // SDL_Point position = { 200, 200 };
  SDL_Point sector = { 1, 1 };
  SDL_Point wheelAxle = { 0, 0 };
  SDL_Rect position = { 70, 70, 8, 16 };
  float x;
  float y;
  int speed = 0;
  int direction = 0; // in degrees

  void update(DegreeCalculator *degrees) {
    x += degrees -> getDegrees(direction, 0) * speed;
    y += degrees -> getDegrees(direction, 1) * speed;
    position.x = x;
    position.y = y;
    sector.x = x / 64;
    sector.y = y / 64;
  }

  // void setTexture(SDL_Texture *settexture) {
  //   texture = settexture;
  // }
  //
  // void render(SDL_Renderer *renderer) {
  //   SDL_RenderCopyEx(renderer, texture, NULL, &location, direction, &axle, SDL_FLIP_NONE);
  // }
};

Car::Car() {
  init();
}

void Car::init() {
  x = 64*3 + 32; //position
  y = 64*3 + 32;
  speed = 0;
  turn = 0;
  // RENAME THESE
  // 64*3 + 32 = 224
  direction = 0; // Degrees
  position = {224, 224, 8, 16}; // DUNNO
  wheelAxle = { 4, 12 }; // Point to rotate around
}

void Car::update(DegreeCalculator *degrees) {


  prevX = x;
  prevY = y;
  // Update velocity
  x += degrees -> getDegrees(direction, 1) * speed;
  y -= degrees -> getDegrees(direction, 0) * speed;
  position.x = x;
  position.y = y;
  sector.x = x / 64;
  sector.y = y / 64;

}

void Car::downdate(DegreeCalculator *degrees)
{
  // Update velocity
  x = prevX;
  y = prevY;
  position.x = x;
  position.y = y;
}
void Car::bounce()
{
  x = prevX;
  y = prevY;
  position.x = x;
  position.y = y;
  speed= -speed;
}

void Car::setTexture(SDL_Texture *settexture) {
  texture = settexture;
}

void Car::render(SDL_Renderer *renderer) {
  // SDL_RenderCopy(renderer, texture, NULL, &position);


  SDL_RenderCopyEx(renderer, texture, NULL, &position, direction, &wheelAxle, SDL_FLIP_NONE);
}

void Car::turning() {
  switch(turn)
  {
    case 1:
    {
      direction-= DEGREES;
      if(direction < 0)
        direction+= 360;
      break;
    }
    case 2:
    {
      direction+= DEGREES;
      if(direction >=360)
        direction-=360;
      break;
    }
    default:
    {
      break;
    }
  }
}

void Car::turnback() {
  switch(turn)
  {
    case 1:
    {
      direction+= DEGREES;
      if(direction >=360)
        direction-=360;
      break;
    }
    case 2:
    {
      direction-= DEGREES;
      if(direction < 0)
        direction+= 360;
      break;
    }
    default:
    {
      break;
    }
  }
}
