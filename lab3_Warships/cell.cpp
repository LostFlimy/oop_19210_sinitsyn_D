#include "cell.h"

Cell::status Cell::getStatus() const {
    return st;
}

void Cell::setStatus(status st) {
    this->st = st;
}

Cell::Cell(Cell::status st, int x, int y) {
    this->x = x;
    this->y = y;
    this->st = st;
}
