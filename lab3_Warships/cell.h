#pragma once

enum class status{
    CLEAR, SHADED, DAMAGE, SHIP
};

class Cell {
public:
    status getStatus() const;
    void setStatus(status st);
    status st;
    Cell(status st);
    Cell();
};

