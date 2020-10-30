#pragma once
#include<iostream>

enum trit{
    True = 1,
    Unknown = 0,
    False = 2
};

class Trit{
public:
    trit value;

    //default constructor
    Trit();

    //constructor
    Trit(trit curValue);
    operator trit() const;

    //operator &
    Trit operator&(const Trit& hsr) const;
    Trit operator&(const trit& hsr) const;
    friend Trit operator&(const trit& lsr, const Trit& hsr);

    //operator ~
    Trit operator~() const;

    //operator |
    Trit operator|(const Trit& hsr) const;
    Trit operator|(const trit& hsr) const;
    friend Trit operator|(const trit& lsr, const Trit& hsr);

    bool operator ==(const Trit& hsr) const;
    bool operator ==(const trit& hsr) const;
    friend bool operator ==(const trit& lsr, const Trit& hsr);

    friend std::ostream& operator<<(std::ostream& stream, Trit t);
};



