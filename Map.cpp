#include "Map.h"

extern const int WINDOW_Y;
extern const int WINDOW_X;

Map::Map() {
    numberRows = (WINDOW_Y-100)/10;
    numerColumns = WINDOW_X/10;

    if((numerColumns > 0) && (numberRows > 0)) {
        ptrMap = new Cell*[numberRows];
        for(int i=0; i<numberRows; i++)
            ptrMap[i] = new Cell[numerColumns];
    }
}

Map::~Map() {
    if((numerColumns > 0) && (numberRows > 0)) {
        for(int i=0; i<numberRows; i++)
            delete [] ptrMap[i];
        delete [] ptrMap;
    }
}

Map::Map(const Map& cm) {
    if(((numberRows == cm.numberRows) && (numberRows > 0)) && ((numerColumns == cm.numerColumns) && (numerColumns > 0))) {
        for(int i=0; i<numberRows; i++) {
            for(int j=0; j<numerColumns; j++)
                ptrMap[i][j].setCell(cm.ptrMap[i][j].getCell());
        }
    }
}

Map& Map::operator=(const Map& cm)
{
    if(((numberRows == cm.numberRows) && (numberRows > 0)) && ((numerColumns == cm.numerColumns) && (numerColumns > 0))) {
        for(int i=0; i<numberRows; i++) {
            for(int j=0; j<numerColumns; j++)
                ptrMap[i][j].setCell(cm.ptrMap[i][j].getCell());
        }
    }

    return *this;
}

void Map::setMapPos(int mx, int my, bool cs)
{
    if(((mx < numerColumns) && (mx >= 0)) && ((my < numberRows) && (my >= 0)))
        ptrMap[my][mx].setCell(cs);
}

bool Map::getMapPosStatus(int mx, int my)
{
    if(((mx < numerColumns) && (mx >= 0)) && ((my < numberRows) && (my >= 0)))
        return ptrMap[my][mx].getCell();
    else
        return false;
}
