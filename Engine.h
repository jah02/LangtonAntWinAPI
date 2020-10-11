#ifndef ENGINE_H
#define ENGINE_H

#include "Map.h"

class Engine {

private:
    Map* cellMap;
    int currentDirection;
    int antX, antY;

protected:
    int getAntPosX() {return antX;}
    int getAntPosY() {return antY;}
    int getCurrentDirection() {return currentDirection;}
    bool setAntPos(int ax, int ay);
    int getRows() {return cellMap->getRows();}
    int getColumns() {return cellMap->getColumns();}
    bool getMapCellStatus(int mx, int my) {return cellMap->getMapPosStatus(mx, my);}

public:
    Engine();
    virtual ~Engine() {cellMap->~Map();}
    Engine(const Engine& ce) {}
    Engine& operator=(const Engine& ce) {return *this;}

    enum directions { NORTH, WEST, SOUTH, EAST };
    enum colors { EMPTY, COLORED };
    virtual void play();
};

#endif // ENGINE_H
