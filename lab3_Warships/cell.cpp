#include "cell.h"

status Cell::getStatus() const {
    return st;
}

void Cell::setStatus(status st) {
    this->st = st;
}

Cell::Cell(status st) {
    this->st = st;
}

Cell::Cell() {
    this->st = status::CLEAR;
}
