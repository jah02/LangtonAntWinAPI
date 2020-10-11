#ifndef CELL_H
#define CELL_H

class Cell {

private:
    bool status;

public:
    Cell() {status = false;}
    ~Cell() {}
    Cell(const Cell& cc);
    Cell& operator=(const Cell& cc);

    bool getCell() {return status;}
    void setCell(bool cv) {status = cv;}
};

#endif // CELL_H
