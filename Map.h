#ifndef MAP_H
#define MAP_H

#include "Cell.h"

class Map {

private:
    Cell** ptrMap;
    int numberRows, numerColumns;

public:
    Map();
    ~Map();
    Map(const Map& cm);
    Map& operator=(const Map& cm);

    void setMapPos(int mx, int my, bool v);
    bool getMapPosStatus(int mx, int my);
    int getRows() {return numberRows;}
    int getColumns() {return numerColumns;}
};

#endif // MAP_H
