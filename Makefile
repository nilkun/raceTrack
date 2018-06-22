SOURCEFILES=raceTrack.cpp eventHandler.cpp tiles.cpp files.cpp car.cpp helpFuncs.cpp
GAMEENGINE=../gameEngine/CreatorTools.o ../gameEngine/fileManager.o ../gameEngine/initialization.o ../gameEngine/rendering.o ../gameEngine/viewport.o
UPDATING=../gameEngine/collisionDetection/collisionDetection.cpp tryouts.cpp
TARGETFILE=race
LFLAGS= -Wall
CFLAGS=-lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf
COMPILER=g++
all:
	$(COMPILER) $(LFLAGS) -o $(TARGETFILE) $(SOURCEFILES) $(GAMEENGINE) $(UPDATING) $(CFLAGS)
