#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__
#include <SDL2/SDL.h>


enum Actions { DEFAULT, RESIZE, QUIT, CLICKED_LEFT, CLICKED_RIGHT, ESCAPE, UP, DOWN, LEFT, RIGHT, KEYDOWN, TEXTINPUT, BACKSPACE, F1, F2 };

struct Mouse {
  int x;
  int y;
};

class EventHandler{


public:
  SDL_Event event;
  EventHandler();
  Actions processEvents();
  int action;
  Mouse mouse;
};
#endif
