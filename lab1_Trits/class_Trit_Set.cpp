#include "class_Trit_Set.h"


size_t TritSet::capacity() const {
    return size;
}

TritSet& TritSet::operator=(TritSet hsr) {
    set = hsr.set;
    size = hsr.size;
    last = hsr.last;
    HaveNotUnknown = hsr.HaveNotUnknown;
    last_is_changed = hsr.last_is_changed;
    last_is_Unknown = hsr.last_is_Unknown;
    return *this;
}

TritSet::TritSet(size_t count_of_trits) {
    set.resize(count_of_trits * 2 / (8 * sizeof(uint32_t))
                + ( (count_of_trits * 2 % (8 * sizeof(uint32_t))) == 0?0:1));
    size = count_of_trits;
    first_size = count_of_trits;
    last = 0;
    last_is_changed = false;
    last_is_Unknown = true;
    HaveNotUnknown = false;
}

TritSet::TritSet() {
    set.clear();
    size = 0;
    last = 0;
    first_size = 0;
    last_is_Unknown = true;
    last_is_changed = false;
    HaveNotUnknown = false;
}

Trit TritSet::getAt(size_t index) const {
    uint32_t cell = set[index * 2 / (8 * sizeof(uint32_t))];
    size_t shift = (index % (sizeof(uint32_t) * 8 / 2));
    return static_cast<Trit>(trit( (uint32_t)0b11 & (cell >> shift * 2) ));
}

void TritSet::setAt(size_t index, Trit value) {
    uint32_t set_cell = index / (16);
    if(index >= capacity()){
        size = index + 1;
        set.resize(set_cell + 1, 0);
    }
    if(index >= last || !last_is_changed) {
        last_is_changed = true;
        last = index;
        if (value == Unknown)
            last_is_Unknown = true;
        else
            last_is_Unknown = false;
    }
    if(!(value == Unknown)){
        HaveNotUnknown = true;
    }
    uint32_t val = 0b00;
    if(value == Trit(False))
        val = 0b10;
    if(value == Trit(True))
        val = 0b01;
    uint32_t shift = index % (sizeof(uint32_t) * 8 / 2);
    uint32_t mask = 0b11 << (shift * 2);
    mask = ~mask;
    set[set_cell] &= mask;
    set[set_cell] ^= (val << shift * 2);
}

void TritSet::setAt(size_t index, trit value) {
    uint32_t set_cell = index / (16);
    if(index >= capacity()){
        size = index + 1;
        set.resize(set_cell + 1, 0);
    }
    if(index >= last || !last_is_changed) {
        last_is_changed = true;
        last = index;
        if (value == Unknown)
            last_is_Unknown = true;
        else
            last_is_Unknown = false;
    }
    if(!(value == Unknown)){
        HaveNotUnknown = true;
    }
    uint32_t val = 0b00;
    if(value == False)
        val = 0b10;
    if(value == True)
        val = 0b01;
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

TritSet TritSet::operator~() {
    for(size_t i = 0; i < capacity(); ++i){
        setAt(i, ~(getAt(i)));
    }
    return *this;
}

TritSet::TritProxy TritSet::operator[](const size_t index) {
    return TritProxy(*this, index);
}

Trit TritSet::operator[](const size_t index) const {
    if(index > size - 1) {
        return (Trit)Unknown;
    }
    return getAt(index);
}

TritSet::TritProxy::TritProxy(TritSet &tritSet, size_t index) : set(tritSet), where(index) {}

TritSet::TritProxy::operator Trit() const {
    return (const_cast<const TritSet&>(set))[where];
}

TritSet::TritProxy &TritSet::TritProxy::operator=(trit hsr) {
    if(where >= set.capacity()){
        if(hsr == Unknown){
            return *this;
        }
    }
    set.setAt(where, Trit(hsr));
    return *this;
}

TritSet::TritProxy &TritSet::TritProxy::operator=(Trit hsr) {
    if(where >= set.capacity()){
        if(hsr == Unknown){
            return *this;
        }
    }
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

Trit operator&(const Trit &lsr, const TritSet::TritProxy &hsr) {
    return (lsr & (Trit)(hsr));
}

Trit operator|(const Trit &lsr, const TritSet::TritProxy &hsr) {
    return (lsr | (Trit)(hsr));
}


void TritSet::shrink() {
    if(!last_is_Unknown){
        set.resize(last/16 + 1);
        size = last + 1;
        last_is_Unknown = False;
        return;
    }
    size_t curlast = lastNotUnknownIndex();
    if(last_is_changed && curlast != first_size){
        set.resize(curlast/16 + (curlast%16 == 0?0:1));
        size = curlast + 1;
        last_is_Unknown = False;
        return;
    }
    size = first_size;
    set.resize(first_size / 16 + 1);
}

size_t TritSet::lastNotUnknownIndex() const{
    int cell = set.size() - 1;
    bool cellIsChanged = false;
    for(int i = set.size() - 1; i >= 0; --i){
        uint32_t mask = ~0;
        if((set[i] & mask) != 0){
            cell = i;
            cellIsChanged = true;
            break;
        }
    }
    if(!cellIsChanged) {
        return first_size;
    }
    size_t index = 16 * (cell + 1) - 1;
    for(size_t i = index; i >= index - 15; --i){
        if(getAt(i) != Unknown) {
            index = i;
            break;
        }
    }
    return index;
}

long long TritSet::length() const {
    size_t curlast = lastNotUnknownIndex();
    if(!HaveNotUnknown){
        return 0;
    }
    return (long long)curlast + 1;
}

void TritSet::trim(size_t lastIndex) {
    size_t cell = lastIndex / 16 + (lastIndex % 16 == 0?0:1);
    for(size_t i = cell; i < set.size() ; ++i) {
        set[i] = 0;
    }
    for(size_t i = lastIndex; i < cell * 16; ++i) {
        setAt(i, Unknown);
    }
    last = (lastIndex <= last? lastIndex: last);
    if(getAt(lastIndex) == Unknown) {
        last_is_Unknown = true;
    } else {
        last_is_Unknown = false;
    }
    if(lastNotUnknownIndex() == first_size && getAt(lastNotUnknownIndex()) == Unknown){
        HaveNotUnknown = false;
    }
}

size_t TritSet::cardinality(Trit value) {
    size_t sum = 0;
    if(value == Unknown) {
        for(int i = last; i > -1; --i){
            if(getAt(i) == Unknown)
                sum++;
        }
    } else {
        for(int i = lastNotUnknownIndex(); i > -1; --i){
            if(getAt(i) == value)
                sum++;
        }
    }
    return sum;
}

size_t TritSet::size_cells() const {
    return (*this).set.size();
}



