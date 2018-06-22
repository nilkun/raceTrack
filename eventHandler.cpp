#include "eventHandler.h"

EventHandler::EventHandler() {  };

Actions EventHandler::processEvents(){
  while(SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT: {
        return QUIT;
      }
      case SDL_MOUSEBUTTONDOWN:
        switch (event.button.button)
        {
          case SDL_BUTTON_LEFT:
          {
            SDL_GetMouseState(&mouse.x, &mouse.y);
            return CLICKED_LEFT;
          }
          case SDL_BUTTON_RIGHT:
          {
             SDL_GetMouseState(&mouse.x, &mouse.y);
             return CLICKED_RIGHT;
          }
        }
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
          case SDLK_ESCAPE:
          {
            return ESCAPE;
          }
          case SDLK_BACKSPACE:
          {
            return BACKSPACE;
          }
          case SDLK_UP:
          {
            return UP;
          }
          case SDLK_DOWN:
          {
            return DOWN;
          }
          case SDLK_LEFT:
          {
            return LEFT;
          }
          case SDLK_RIGHT:
          {
            return RIGHT;
          }
          case SDLK_F1:
          {
            return F1;
          }
          case SDLK_F2:
          {
            return F2;
          }
          return KEYDOWN;
        }

      case SDL_TEXTINPUT:
      {
        return TEXTINPUT;
      }

      case SDL_WINDOWEVENT:
      {
        switch (event.window.event) {
          case SDL_WINDOWEVENT_RESIZED:
          {
            return RESIZE;
          }
          return DEFAULT;
        }
        return DEFAULT;
      }
    }
  }
  return DEFAULT;
}
