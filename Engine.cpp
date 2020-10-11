#include "Engine.h"

Engine::Engine() {
    cellMap = new Map();
    antX = 35;
    antY = 18;
    currentDirection = NORTH;
}

bool Engine::setAntPos(int ax, int ay) {
    if(((ax >= 0) && (ax < cellMap->getColumns()-1)) && ((ay >= 0) && (ay < cellMap->getRows()-3))) { //-1 and -4 draw correction
        antX = ax;
        antY = ay;
        return true;
    } else
        return false;
}

void Engine::play() {
    //Set current cell to reverse value
    if(cellMap->getMapPosStatus(antX, antY) == EMPTY)
        cellMap->setMapPos(antX, antY, true);
    else
        cellMap->setMapPos(antX, antY, false);


    //Move ant x,y, and set next direction
    switch(currentDirection) {
        case NORTH:
            if((antY-1) >= 0)
                antY--;
            else
                antY = cellMap->getRows()-5; //-5 draw correction

            if(cellMap->getMapPosStatus(antX, antY) == EMPTY)
                currentDirection = EAST;
            else
                currentDirection = WEST;

            break;

        case WEST:
            if((antX-1) >= 0)
                antX--;
            else
                antX = cellMap->getColumns()-2; //-2 draw correction

            if(cellMap->getMapPosStatus(antX, antY) == EMPTY)
                currentDirection = NORTH;
            else
                currentDirection = SOUTH;

            break;

        case SOUTH:
            if((antY+1) < cellMap->getRows()-3) //-3 draw correction
                antY++;
            else
                antY = 0;

            if(cellMap->getMapPosStatus(antX, antY) == EMPTY)
                currentDirection = WEST;
            else
                currentDirection = EAST;

            break;

        case EAST:
            if((antX+1) < cellMap->getColumns()-1) //-1 draw correction
                antX++;
            else
                antX = 0;

            if(cellMap->getMapPosStatus(antX, antY) == EMPTY)
                currentDirection = SOUTH;
            else
                currentDirection = NORTH;

            break;
    }
}
