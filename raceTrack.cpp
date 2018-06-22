#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../gameEngine/creatorTools/CreatorTools.h"
#include "../gameEngine/fileManager/fileManager.h"
#include "../gameEngine/window/window.h"
#include "../gameEngine/collisionDetection/collisionDetection.h"
#include <iostream>

#include "eventHandler.h"
#include "tiles.h"
#include "files.h"
#include "car.h"
#include "tryouts.h"

// SOME FUNCTIONS, SHOWMESSAGE SHOULD BE ADDED TO GAME ENGINE
void showMessage(SDL_Renderer* renderer, std::string message, FontAtlas *bitfont, int yPos = 300, int xPos = -1);
TextureCreator images;

int main()
{

  srand(time(NULL));

  // THESE SHOULD BE MOVED TO THE TILEMANAGER
  //int tm.tileSize = 64; // SIZE OF INDIVIDUAL TILES
  //SDL_Point tm.currentTile = { 1, 1 }; // CURRENTLY SELECTED TILE

  // Actions input;
  bool running = true;

  // SETUP STARTSCREEN
  Screen screen("Map Editor", 1024, 768);
  screen.init();
  SDL_Renderer *renderer;
  renderer = screen.getRenderer();

  // Load some stuff
  FontAtlas bitfont;
  TileManager tm;
  EventHandler events;
  CollisionDetection collision;

  // Are these needed?
  // images.setColor(255, 0, 0, 0);
  //std::string textString = "Hello World";

  // INITIALIZE VARIABLES
  bitfont = images.create8bitAtlas(renderer);
  tm.newTiles(640, 480, 64);
  tm.textureAtlas = images.fromImage(renderer, "resources/roadSegments.png");
  tm.setStart(3, 3);
  // Set start!

// DEBUG
  SDL_Rect debugViewport = { 800, 0, 224, 768 };

  while(running)
  {
    switch(events.processEvents())
    {
			case QUIT:
			{
				running = false;
				break;
			}
      case UP:
			{
        running = false;
        break;
			}
      case BACKSPACE:
      {
        break;
      }
      case F1:
      {
        std::cout << "Saving..." << std::endl;
        saveTrack(tm);
        break;
      }
      case F2:
      {
        std::cout << "Loading... " << std::endl;
        loadTrack(tm);
        break;
      }
      case CLICKED_LEFT:
      {
        if(events.mouse.x >= 0 && events.mouse.x < 1024
          && events.mouse.y >= 0 && events.mouse.y < 768)
        {
          tm.currentTile.x = events.mouse.x / tm.tileSize;
          tm.currentTile.y = events.mouse.y / tm.tileSize;
          tm.onClick(tm.currentTile);
        }
        break;
      }
      case CLICKED_RIGHT:
      {
        tm.currentTile.x = events.mouse.x / tm.tileSize;
        tm.currentTile.y = events.mouse.y / tm.tileSize;
        tm.destroy(tm.currentTile);
        break;
      }
      case TEXTINPUT:
      {
        break;
      }
      default:
        //ignore
        break;
    }

// RENDER TILES
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    tm.render(renderer);

// DEBUG WINDOW
    SDL_RenderSetViewport(renderer, &debugViewport);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    images.setColor(255, 0, 0, 0);
    showMessage(renderer, "DEBUG WINDOW", &bitfont, 10, 10);
    showMessage(renderer, "x: " + std::to_string(tm.dimension.x), &bitfont, 20, 10);
    showMessage(renderer, "y: " + std::to_string(tm.dimension.y), &bitfont, 30, 10);
    showMessage(renderer, "sel X: " + std::to_string(tm.currentTile.x), &bitfont, 40, 10);
    showMessage(renderer, "sel Y: " + std::to_string(tm.currentTile.y), &bitfont, 50, 10);
    showMessage(renderer, "track length: " + std::to_string(tm.trackLength), &bitfont, 60, 10);
    SDL_RenderSetViewport(renderer, NULL);

    if(tm.courseComplete) running = false;

// RENDER TO SCREEN
    SDL_RenderPresent(renderer);
  }

  running = true;
  DegreeCalculator degrees;
  Car car;
  car.setTexture(images.fromImage(renderer, "resources/car.png"));

  tm.showGrid = false;

  while(running) {
    switch(events.processEvents()) {
			case ESCAPE:
			{
				running=false;
				break;
			}
      case UP:
			{
				car.speed+=.1;
        break;
			}
      case DOWN:
			{
				car.speed-=.08;
        break;
			}
      case LEFT:
			{
				car.turn = 1;
        car.turning();
				break;
			}
      case RIGHT:
			{
        car.turn = 2;
        car.turning();
				break;
			}
      default:
      {
        break;
      }
    }

    car.update(&degrees);

    // CollisionDetection
    SDL_Rect x_coords, y_coords;
    getShape(car.position, x_coords, y_coords, car.direction);
    if(tm.tile[car.sector.x][car.sector.y].tiletype == 1)
    {
      std::cout << "CURVE" << std::endl;
      if(collision.polygonVSCircle(x_coords, y_coords, tm.tile[car.sector.x][car.sector.y].collisionPoint, 10.0f)
        ||(collision.polygonOutCircle(x_coords, y_coords, tm.tile[car.sector.x][car.sector.y].collisionPoint, 54.0f)))
      // if(collision.rectangleVSCircle(car.position, tm.tile[car.sector.x][car.sector.y].collisionPoint, car.direction, 10.0f)
      //   ||(collision.rectangleOutCircle(car.position, tm.tile[car.sector.x][car.sector.y].collisionPoint, car.direction, 54.0f)))
      {
        //car.downdate(&degrees);
        car.bounce();
        car.turnback();
      }
    }
    else if(tm.tile[car.sector.x][car.sector.y].tiletype == 2)
    {
      // std::cout << "STRAIGHT" << std::endl;
      // SDL_Rect yCoords;
      int loc = car.sector.y * 64;
      //collision.getRectangleY(car.position, yCoords, car.direction);
      if(collision.rectangleWithinLine(y_coords, loc+10)
        ||collision.rectangleBeyondLine(y_coords, loc+54))
      {
        car.bounce();
        car.turnback();
      }
      showMessage(renderer, "y: " + std::to_string(loc), &bitfont, 220, 10);
      // showMessage(renderer, "x: " + std::to_string(car.x), &bitfont, 220, 10);
    }
    else if(tm.tile[car.sector.x][car.sector.y].tiletype == 3)
    {
      std::cout << "UP" << std::endl;
      //SDL_Rect yCoords;
      int loc = car.sector.x * 64;
      //collision.getRectangleY(car.position, yCoords, car.direction);
      if(collision.rectangleWithinLine(x_coords, loc+10)
        ||collision.rectangleBeyondLine(x_coords, loc+54))
      {
        car.bounce();
        car.turnback();
      }
    }

    car.turn = 0;

// DEBUG
    SDL_RenderClear(renderer);
    SDL_RenderSetViewport(renderer, &debugViewport);
    showMessage(renderer, "TESTING", &bitfont, 10, 10);
    showMessage(renderer, "x: " + std::to_string(car.x), &bitfont, 20, 10);
    showMessage(renderer, "y: " + std::to_string(car.y), &bitfont, 30, 10);
    showMessage(renderer, "speed: " + std::to_string(car.speed), &bitfont, 40, 10);
    showMessage(renderer, "direction(degrees): " + std::to_string(car.direction), &bitfont, 50, 10);

    showMessage(renderer, "Coordinates: " + std::to_string(x_coords.x) + " " + std::to_string(y_coords.x), &bitfont, 60, 10);

    showMessage(renderer, "             " + std::to_string(x_coords.y) + " " + std::to_string(y_coords.y), &bitfont, 70, 10);
    showMessage(renderer, "             " + std::to_string(x_coords.w) + " " + std::to_string(y_coords.w), &bitfont, 80, 10);
    showMessage(renderer, "             " + std::to_string(x_coords.h) + " " + std::to_string(y_coords.h), &bitfont, 90, 10);
    showMessage(renderer, "in sector " + std::to_string(car.sector.x), &bitfont, 100, 10);
    showMessage(renderer, "in sector " + std::to_string(car.sector.y), &bitfont, 110, 10);
    SDL_RenderSetViewport(renderer, NULL);

    tm.render(renderer);
    car.render(renderer);
    SDL_RenderPresent(renderer);
  }

  return 0;
}


void showMessage(SDL_Renderer *renderer, std::string message, FontAtlas *bitfont, int yPos, int xPos) {
  SDL_Texture *messageTexture = nullptr;
  images.setColor(255, 0, 0, 255);
  SDL_Color setC= { 255, 0, 0, 255 };
  messageTexture = images.fromAtlasToText(renderer, message.c_str(), bitfont, setC);
  int texW = 0;
  int texH = 0;
  SDL_QueryTexture(messageTexture, NULL, NULL, &texW, &texH);
  if(xPos == -1) xPos = (1024 - texW)/2; //centered
  SDL_Rect messageLocation = { xPos, yPos, texW, texH };
//  SDL_RenderSetViewport(renderer, NULL);
  SDL_RenderCopy(renderer, messageTexture, NULL, &messageLocation);
  SDL_DestroyTexture(messageTexture);
}
