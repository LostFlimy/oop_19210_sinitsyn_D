#include "class_Trit.h"

Trit::Trit(trit curValue) {
    value = curValue;
}

Trit Trit::operator&(const Trit &hsr) {
    if(hsr.value == False || value == False)
        return False;
    if(hsr.value == Unknown || value == Unknown)
        return Unknown;
    return True;
}

Trit Trit::operator&(const trit &hsr) {
    if(hsr == False || value == False)
        return False;
    if(hsr == Unknown || value == Unknown)
        return Unknown;
    return True;
}

Trit operator&(const trit &lsr, const Trit &hsr) {
    if(lsr == False || hsr.value == False)
        return False;
    if(lsr == Unknown || hsr.value == Unknown)
        return Unknown;
    return True;
}

Trit Trit::operator~() {
    if(value == Unknown)
        return Unknown;
    if(value == True)
        return False;
    return True;
}

Trit operator~(const trit &x) {
    if(x == Unknown)
        return Unknown;
    if(x == False)
        return True;
    return False;
}

Trit Trit::operator|(const Trit &hsr) {
    if(hsr.value == False && value == False)
        return False;
    if(hsr.value == True || value == True)
        return True;
    return Unknown;
}

Trit Trit::operator|(const trit &hsr) {
    if(hsr == False && value == False)
        return False;
    if(hsr == True || value == True)
        return True;
    return Unknown;
}

Trit operator|(const trit &lsr, const Trit &hsr) {
    if(hsr.value == False && lsr == False)
        return False;
    if(hsr.value == True || lsr == True)
        return True;
    return Unknown;
}

Trit::Trit() {
    value = Unknown;
}

Trit::operator trit() const {
    return value;
}

bool Trit::operator==(const Trit &hsr) {
    if( (value == True && hsr.value == True) ||
        (value == False && hsr.value == False) ||
        (value == Unknown && hsr.value == Unknown)) {
        return true;
    }
    return false;
}

bool Trit::operator==(const trit &hsr) {
    if( (value == True && hsr == True) ||
        (value == False && hsr == False) ||
        (value == Unknown && hsr == Unknown)) {
        return true;
    }
    return false;
}

bool operator==(const trit &lsr, const Trit &hsr) {
    if( (lsr == True && hsr.value == True) ||
        (lsr == False && hsr.value == False) ||
        (lsr == Unknown && hsr.value == Unknown)) {
        return true;
    }
    return false;
}

std::ostream &operator<<(std::ostream &stream, Trit t) {
    if(t == True) {
        stream << "True";
    }
    else if(t == False) {
        stream << "False";
    }
    else {
        stream << "Unknown";
    }
    return stream;
}


