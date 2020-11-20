#pragma once
#include<iostream>

class Cell {
public:
    enum class status{
        CLEAR, SHADED, PENETRATION, SHIP
    };
    status getStatus() const;
    void setStatus(status st);
    int x;
    int y;
    status st;
    Cell(status st, int x, int y);
};

