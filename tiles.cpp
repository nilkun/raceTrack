#include "tiles.h"
#include <iostream>

void TileManager::Tile::init() {
  left = false;
  right = false;
  up = false;
  down = false;
  hasRoad = false;
  isComplete = false;
}
TileManager::Tile::Tile() {
  init();
}
TileManager::Tile::Tile(SDL_Rect where) {
  location = where;
  init();
}

TileManager::TileManager()
{
  startPosition = { 3, 3 };
  showGrid = true;
}

void TileManager::render(SDL_Renderer *renderer) {
  for(auto &vectors : tile)
    for(auto &tile : vectors) {
      SDL_RenderCopy(renderer, textureAtlas, &tile.textureIndex, &tile.location);
      if(showGrid) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
        SDL_RenderDrawRect(renderer, &tile.location);
      }
    }
}

void TileManager::newTiles(int x, int y, int size) {
  init(x, y, size);
}

void TileManager::init(int x, int y, int size)
{
  SDL_Rect copy;
  tileSize = size;
  for(int i = 0; i < x; i+=size){
    std::vector <Tile> xTiles;

    for(int j = 0; j < y; j+=size) {
      copy = { i, j, size, size };
      xTiles.push_back(copy);
      xTiles.back().textureIndex = { 192, 0, 64, 64 };
    }
    tile.push_back(xTiles);
  }
  dimension.x = tile.size();
  dimension.y = tile[0].size();
}

void TileManager::onClick(SDL_Point &at) {
  // Prevent out of bounds
  if(at.x>=dimension.x || at.y>=dimension.y) return;

  // unlock start location if track is long enough
  // if(trackLength==3) {
  //   // tile[startPosition.x][startPosition.y].hasRoad = false;
  //   tile[startPosition.x][startPosition.y].isComplete = false;
  // }
// if(trackLength<1)
    // Check that current tile is not completed
    // or if it is start tile
  if(!tile[at.x][at.y].isComplete
    || (at.x == startPosition.x && at.y == startPosition.y))
  {
    for(int i = 0; i < 4; i++)
    {
      SDL_Point current = at;
      if(i==0)
      {
        current.x--;
        if(current.x < 0) continue;
      }
      else if(i==1)
      {
        current.x++;
        if(current.x >= dimension.x) continue;
      }
      else if(i==2)
      {
        current.y--;
        if(current.y < 0) continue;
      }
      else if(i==3)
      {
        current.y++;
        if(current.y >= dimension.y) continue;
      }

      // Check if adjacent tile has road and is not complete
      // And then set it up! DONT FORGET START COMPARISON!!!
      if(tile[current.x][current.y].hasRoad
        && !tile[current.x][current.y].isComplete)
      {
        tile[at.x][at.y].hasRoad = true;

        switch(i)
        {
          case 0: {
            tile[at.x][at.y].left = true;
            tile[current.x][current.y].right = true;
            break;
          }
          case 1: {
            tile[at.x][at.y].right = true;
            tile[current.x][current.y].left = true; break;
          }
          case 2: {
            tile[at.x][at.y].up = true;
            tile[current.x][current.y].down = true; break;
          }
          case 3: {
            tile[at.x][at.y].down = true;
            tile[current.x][current.y].up = true; break;
          }
        }
        tile[current.x][current.y].isComplete = true;
        setTexture(tile[current.x][current.y]);
        setTexture(tile[at.x][at.y]);
        trackLength++;
        // Check if current tile is start, if that is the case, then the course is completed!
        if (at.x==startPosition.x && at.y==startPosition.y)
        {
            courseComplete = true;
            //std::cout << "COURSE COMPLETED!!!" << std::endl;
        }
      }
    }
  }
}



// LATER!!!  SEE IF TRACK IS COMPLETE!!!

  // if(trackLength==3) {
  //   // make start available
  //   tile[startPosition.x][startPosition.y].hasRoad = false;
  // }
  // if(!tile[selectedTile.x][selectedTile.y].hasRoad) {
  //
  //   if(startPosition.x == selectedTile.x && startPosition.y == selectedTile.y && trackLength > 3 ) {
  //   tile[at.x-1][at.y].right = true;
  //   tile[at.x-1][at.y].isComplete = true;
  //   setTexture(tile[at.x-1][at.y]);
  //   trackLength++;
  //   }



void TileManager::destroy(SDL_Point &at) {
  // Prevent out of bounds
  if(at.x>=dimension.x || at.y>=dimension.y) return;

  // CHECK IF DESTROYABLE
  // I.E. IF IT HAS AN INCOMPLETE ROAD && IS NOT THE START TILE
  if(
    tile[at.x][at.y].hasRoad
    && !(at.x == startPosition.x
      && at.y == startPosition.y)
    && !tile[at.x][at.y].isComplete)
  {
    // then remove
    // first clean up adjacent road

    trackLength--;
    SDL_Point edit = at;
    enum direction { LEFT, RIGHT, UP, DOWN };
    direction setFalse;

    // Tile* adjacent;
    // set tile to edit and where to edit
    if (tile[at.x][at.y].left)
    {
      edit.x--; setFalse = RIGHT; tile[at.x][at.y].left = false;
    }
    else if(tile[at.x][at.y].right)
    {
      edit.x++; setFalse = LEFT; tile[at.x][at.y].right = false;
    }
    else if(tile[at.x][at.y].up)
    {
      edit.y--; setFalse = DOWN; tile[at.x][at.y].up = false;
    }
    else if(tile[at.x][at.y].down)
    {
      edit.y++; setFalse = UP; tile[at.x][at.y].down = false;
    }
    // Adjacent tile no longer complete
    tile[edit.x][edit.y].isComplete = false;

    switch(setFalse)
    {
      case RIGHT:
        tile[edit.x][edit.y].right = false;
        break;
      case LEFT:
        tile[edit.x][edit.y].left = false;
        break;
      case UP:
        tile[edit.x][edit.y].up = false;
        break;
      case DOWN:
        tile[edit.x][edit.y].down = false;
        break;
    }
    // Clean up empty tile
    tile[at.x][at.y].hasRoad = false;
    setTexture(tile[at.x][at.y]);
    setTexture(tile[edit.x][edit.y]);
  }
}

void TileManager::setTexture(Tile &tile) {
  if(!tile.hasRoad && (tile.location.x != startPosition.x || tile.location.y != startPosition.y )) {
    tile.textureIndex = { 192, 0, 64, 64 };
  }
  else if (tile.left) {
    if (tile.right) {
      tile.textureIndex = { 0, 64, 64, 64 };
      tile.tiletype=2;
    }
    else if(tile.down) {
      tile.textureIndex = { 128, 0, 64, 64 };
      tile.tiletype=1;
      tile.collisionPoint = { tile.location.x, tile.location.y + tileSize };
    }
    else if(tile.up)
    {
      tile.textureIndex = { 128, 64, 64, 64 };
      tile.tiletype=1;
      tile.collisionPoint = { tile.location.x, tile.location.y };
    }
    // DEFAULT TO STRAIGHT
    else
    {
      tile.textureIndex = { 0, 64, 64, 64 };
    }
  }
  else if (tile.right) {
    if(tile.down)
    {
      tile.textureIndex = { 64, 0, 64, 64 };
      tile.tiletype=1;
      tile.collisionPoint = { tile.location.x + tileSize, tile.location.y + tileSize };
    }
    else if(tile.up)
    {
      tile.textureIndex = { 64, 64, 64, 64 };
      tile.tiletype=1;
      tile.collisionPoint = { tile.location.x + tileSize, tile.location.y };
    }
    else tile.textureIndex = { 0, 64, 64, 64 };
  }
  // JUST A STRAIGHT LINE
  else
  {
    tile.textureIndex = { 0, 0, 64, 64 };
    tile.tiletype=3;
  }
}

void TileManager::setStart(int x, int y)
{
  startPosition.x = x;
  startPosition.y = y;
  tile[x][y].textureIndex = { 192, 64, 64, 64 };
  tile[x][y].hasRoad = true;
}
