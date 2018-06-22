#ifndef __TILES_H__
#define __TILES_H__

#include  <SDL2/SDL.h>
#include <vector>

class TileManager {
public:
  // enum Tiletype { CURVE, LEFTRIGHT, UPDOWN };
  struct Tile {

      SDL_Rect location;
      SDL_Rect textureIndex;
      bool left, right, up, down, hasRoad, isComplete;
      void init();
      Tile();
      Tile(SDL_Rect where);
      // Tiletype
      char tiletype;
      SDL_Point collisionPoint;

  };
  void setTexture(Tile &tile);

public:
  // Currently not saved or loaded

    // LEFTRIGHT, LEFTUP, LEFTDOWN, UPRIGHT, UPDOWN, RIGHTDOWN }
  int tileSize;
  bool showGrid;
  SDL_Point currentTile;

  std::vector< std::vector <Tile> > tile;
  SDL_Point startPosition;
  SDL_Point dimension; // SIZE OF MAP IN TILES
  SDL_Texture *textureAtlas;
  bool courseComplete = false;
  int trackLength = 0;
  TileManager();

  void render(SDL_Renderer *renderer);
  void newTiles(int x, int y, int size);
  void init(int x, int y, int tilesize);
  void onClick(SDL_Point &selectedTile);
  void destroy(SDL_Point &selectedTile);
  void setStart(int x, int y);
};


#endif
