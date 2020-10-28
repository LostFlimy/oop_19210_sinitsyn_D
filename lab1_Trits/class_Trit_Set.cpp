#include "class_Trit_Set.h"


size_t TritSet::capacity() const {
    return set.size();
}

TritSet& TritSet::operator=(TritSet hsr) {
    set = hsr.set;
    size = hsr.size;
    return *this;
}

TritSet::TritSet(size_t count_of_trits) {
    set.resize(count_of_trits * 2 / (8 * sizeof(uint32_t)) + 1);
    size = count_of_trits;
    last = -1;
}

TritSet::TritSet() {
    set.clear();
    size = 0;
    last = -1;
}

Trit TritSet::getAt(size_t index) const {
    uint32_t cell = set[index * 2 / (32 * 8)];
    size_t shift = (index % (sizeof(uint32_t) * 8 / 2));
    return static_cast<Trit>(trit( (uint32_t)0b11 & (cell >> shift * 2) ));
}

void TritSet::setAt(size_t index, Trit value) {
    uint32_t val = 0b00;
    if(value == Trit(False))
        val = 0b10;
    if(value == Trit(True))
        val = 0b01;
    uint32_t set_cell = index / (16 * 8);
    uint32_t shift = index % (sizeof(uint32_t) * 8 / 2);
    uint32_t mask = 0b11 << (shift * 2);
    mask = ~mask;
    set[set_cell] &= mask;
    set[set_cell] ^= (val << shift * 2);
}

void TritSet::setAt(size_t index, trit value) {
    uint32_t val = 0b00;
    if(value == False)
        val = 0b10;
    if(value == True)
        val = 0b01;
    uint32_t set_cell = index / (16 * 8);
    uint32_t shift = index % (sizeof(uint32_t) * 8 / 2);
    uint32_t mask = 0b11 << (shift * 2);
    mask = ~mask;
    set[set_cell] &= mask;
    set[set_cell] ^= (val << (shift * 2));
}

TritSet TritSet::operator&(TritSet hsr) {
    size_t res_size = min(capacity(), hsr.capacity());
    TritSet res(res_size);
    for(size_t i = 0; i < res_size; ++i){
        Trit x = getAt(i);
        Trit y = hsr.getAt(i);
        res.setAt(i, (x & y));
    }
    return res;
}

TritSet TritSet::operator|(TritSet hsr) {
    TritSet res;
    if(capacity() > hsr.capacity()) {
        res = *this;
        for(size_t i = 0; i < hsr.capacity(); ++i) {
            res.setAt(i, (getAt(i) | hsr.getAt(i)));
        }
    }
    else {
        res = hsr;
        for(size_t i = 0; i < capacity(); ++i) {
            res.setAt(i, (getAt(i) | hsr.getAt(i)));
        }
    }
    return res;
}

TritSet TritSet::operator!() {
    for(size_t i = 0; i < capacity(); ++i){
        setAt(i, ~(getAt(i)));
    }
    return *this;
}

TritSet::TritProxy TritSet::operator[](const size_t index) {
    return TritProxy(*this, index);
}

Trit TritSet::operator[](size_t index) const {
    if(index > size - 1) {
        return (Trit)Unknown;
    }
    return (*this).getAt(index);
}

void TritSet::push(Trit new_value) {
    last += 1;
    setAt(last, new_value);
}

Trit TritSet::lastTrit() {
    return getAt(last);
}

int32_t TritSet::lastpos() {
    return last;
}

TritSet::TritProxy::TritProxy(TritSet &tritSet, size_t index) : set(tritSet), where(index) {}

TritSet::TritProxy::operator Trit() const {
    return (const_cast<const TritSet&>(set))[where];
}

TritSet::TritProxy &TritSet::TritProxy::operator=(trit hsr) {
    set.setAt(where, Trit(hsr));
    return *this;
}

TritSet::TritProxy &TritSet::TritProxy::operator=(Trit hsr) {
    set.setAt(where, hsr);
    return *this;
}

bool TritSet::TritProxy::operator==(const Trit &hsr) {
    return ((Trit)(*this) == hsr);
}

Trit TritSet::TritProxy::operator&(const Trit &hsr) {
    return ((Trit)(*this) & hsr);
}

Trit TritSet::TritProxy::operator|(const Trit &hsr) {
    return ((Trit)(*this) | hsr);
}

Trit TritSet::TritProxy::operator~() {
    return (~(Trit)(*this));
}

ostream &operator<<(ostream &stream, TritSet::TritProxy proxy) {
    stream << (Trit)proxy;
    return stream;
}

