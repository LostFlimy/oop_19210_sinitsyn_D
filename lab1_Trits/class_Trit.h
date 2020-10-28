#ifndef LAB1_TRITS_CLASS_TRIT_H
#define LAB1_TRITS_CLASS_TRIT_H
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
    Trit operator&(const Trit& hsr);
    Trit operator&(const trit& hsr);
    friend Trit operator&(const trit& lsr, const Trit& hsr);

    //operator ~
    Trit operator~();
    friend Trit operator~(const trit& x);

    //operator |
    Trit operator|(const Trit& hsr);
    Trit operator|(const trit& hsr);
    friend Trit operator|(const trit& lsr, const Trit& hsr);

    bool operator ==(const Trit& hsr);
    bool operator ==(const trit& hsr);
    friend bool operator ==(const trit& lsr, const Trit& hsr);

    friend std::ostream& operator<<(std::ostream& stream, Trit t);
};




#endif //LAB1_TRITS_CLASS_TRIT_H
