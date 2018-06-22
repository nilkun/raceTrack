#include <vector>
#include "../gameEngine/fileManager/fileManager.h"
#include "files.h"

void saveTrack(TileManager &tm) {

  // Create save instance
  FileManager saving;
  // OPEN SAVEFILE
  saving.openToSave("track.data");

  // FIRST WRITE THE TRACK DATA
  saving.writeData(tm.startPosition);
  saving.writeData(tm.dimension);
  saving.writeData(tm.courseComplete);
  saving.writeData(tm.trackLength);

  for(auto &rows : tm.tile) {
    for(auto &currentTile : rows) {
      // Write data to file
      saving.writeData(currentTile.location);
      saving.writeData(currentTile.textureIndex);
      saving.writeData(currentTile.left);
      saving.writeData(currentTile.right);
      saving.writeData(currentTile.up);
      saving.writeData(currentTile.down);
      saving.writeData(currentTile.hasRoad);
      saving.writeData(currentTile.isComplete);
    }
  }
  // CLOSE SAVEFILE
  saving.close();
};

void loadTrack(TileManager &tm)
{
    // Create load instance
    FileManager loading;
    // OPEN SAVEFILE
    loading.load("track.data");

    // FIRST WRITE THE TRACK DATA
    loading.readData(tm.startPosition);
    loading.readData(tm.dimension);
    loading.readData(tm.courseComplete);
    loading.readData(tm.trackLength);

    // currentTile
    // Improve by clearing vector and then making a new vector with dimensions.
    for(auto &rows : tm.tile) {
      for(auto &currentTile : rows) {
        // Write data to file
        loading.readData(currentTile.location);
        loading.readData(currentTile.textureIndex);
        loading.readData(currentTile.left);
        loading.readData(currentTile.right);
        loading.readData(currentTile.up);
        loading.readData(currentTile.down);
        loading.readData(currentTile.hasRoad);
        loading.readData(currentTile.isComplete);
        tm.setTexture(currentTile);
      }
    }
    if(tm.trackLength==0) {
      tm.setStart(tm.startPosition.x, tm.startPosition.y);
    }
    // tm.tile[startPosition.x][startPosition].hasRoad = true;
    // tm.tile[3][3].textureIndex = { 192, 64, 64, 64 };
    // CLOSE SAVEFILE
    loading.close();
}
