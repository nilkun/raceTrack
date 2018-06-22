#include "helpFuncs.h"

void drawCircleAdv(SDL_Renderer *renderer, int radiusInPixels) {
  int location[radiusInPixels];
  for(int i = 0; i < radiusInPixels; i++) {
    location[i] = sqrt(radiusInPixels*radiusInPixels - i * i);
  }
  int offsetX = radiusInPixels;
  int offsetY = radiusInPixels;

  for(int i = 0; i < radiusInPixels; i++) {
    SDL_RenderDrawPoint(renderer, offsetX + i, offsetY + location[i]);
    SDL_RenderDrawPoint(renderer, offsetX + i, offsetY - location[i]);
    SDL_RenderDrawPoint(renderer, offsetX - i, offsetY + location[i]);
    SDL_RenderDrawPoint(renderer, offsetX - i, offsetY - location[i]);
    SDL_RenderDrawPoint(renderer, offsetX + location[i], offsetY + i);
    SDL_RenderDrawPoint(renderer, offsetX + location[i], offsetY - i);
    SDL_RenderDrawPoint(renderer, offsetX - location[i], offsetY + i);
    SDL_RenderDrawPoint(renderer, offsetX - location[i], offsetY - i);
  }
}

void drawCircle(SDL_Renderer *renderer) { // USING DEGREES
  int radius = 20;
  double PI = 3.14159265;
  double calculate[360][2];

  for(int angle=0; angle<90; angle++) {
    float angleRad = PI * angle / 180;
    calculate[angle][0] = cos(angleRad);
    calculate[angle][1] = sin(angleRad);

    calculate[angle+90][1] = calculate[angle][0];
    calculate[angle+90][0] = -calculate[angle][1];

    calculate[angle+180][0] = -calculate[angle][0];
    calculate[angle+180][1] = -calculate[angle][1];

    calculate[angle+270][0] = calculate[angle][1];
    calculate[angle+270][1] = -calculate[angle][0];
  }
  SDL_SetRenderDrawColor(renderer, 0,255,0,0);

  for(int i=1; i<360; i++) {
    SDL_RenderDrawLine(renderer,
      30+(radius * calculate[i][0]),
      30+(radius * calculate[i][1]),
      30+(radius * calculate[i-1][0]),
      30+(radius * calculate[i-1][0])
    );
  }
  SDL_RenderDrawLine(renderer,
    radius * calculate[0][0],
    radius * calculate[0][1],
    radius * calculate[359][0],
    radius * calculate[359][0]
  );
}

DegreeCalculator::DegreeCalculator() {
//  float calculate[360][2] = {};
  double PI = 3.14159265;
  for(int angle=0; angle<90; angle++) {
    float angleRad = PI * angle / 180;
    calculate[angle][0] = cos(angleRad);
    calculate[angle][1] = sin(angleRad);

    calculate[angle+90][1] = calculate[angle][0];
    calculate[angle+90][0] = -calculate[angle][1];

    calculate[angle+180][0] = -calculate[angle][0];
    calculate[angle+180][1] = -calculate[angle][1];

    calculate[angle+270][0] = calculate[angle][1];
    calculate[angle+270][1] = -calculate[angle][0];
  }
}

float DegreeCalculator::getDegrees(int degrees, int XorY) {
  return calculate[degrees][XorY];
}
