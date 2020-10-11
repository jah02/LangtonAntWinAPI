#include "Cell.h"

Cell::Cell(const Cell& cs)
{
    if(status != cs.status)
        status = cs.status;
}

Cell& Cell::operator=(const Cell& cs)
{
    if(status != cs.status)
        status = cs.status;

    return *this;
}
