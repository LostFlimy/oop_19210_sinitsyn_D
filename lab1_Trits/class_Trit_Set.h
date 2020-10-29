#pragma once
#include "class_Trit.h"
#include <cstdint>
#include <vector>

using namespace std;

/*00 = unknown
 * 10 = False
 * 01 = True
 */

class TritSet{
private:
    vector<uint32_t> set;
    size_t size;
    size_t last;
    bool last_is_Unknown;
    size_t lastNotUnknownIndex() const;
public:
    class TritProxy{
    private:
        TritSet& set;
        size_t where;
        friend class TritSet;
    public:
        TritProxy(TritSet& tritSet, size_t index);
        operator Trit() const;

        TritProxy& operator =(trit hsr);
        TritProxy& operator =(Trit hsr);

        bool operator ==(const Trit& hsr);

        Trit operator &(const Trit& hsr);
        friend Trit operator &(const Trit& lsr, const TritProxy& hsr);

        Trit operator |(const Trit& hsr);
        friend Trit operator |(const Trit& lsr, const TritProxy& hsr);

        Trit operator ~();

        friend ostream& operator <<(ostream& stream, TritProxy proxy);
    };

    TritSet();

    explicit TritSet(size_t count_of_trits);

    [[nodiscard]] size_t capacity() const;

    TritSet& operator =(TritSet hsr);

    Trit getAt(size_t index) const;

    void setAt(size_t index, Trit value);
    void setAt(size_t index, trit value);

    TritSet operator &(TritSet hsr);

    TritSet operator |(TritSet hsr);

    TritSet operator !();

    TritProxy operator [](size_t index);

    Trit operator [](size_t index) const;

    void shrink();

    size_t length() const;

    void trim(size_t lastIndex);

    size_t cardinality(Trit value);
};




