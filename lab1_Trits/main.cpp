#include <iostream>
#include "class_Trit_Set.h"
#include <gtest/gtest.h>

using namespace std;

TEST(classtrit, logicEqual) {
    Trit a(True);
    Trit b(Unknown);
    Trit c(False);

    ASSERT_TRUE(a == True);
    ASSERT_TRUE(b == Unknown);
    ASSERT_TRUE(c == False);

    ASSERT_FALSE(a == False);
    ASSERT_FALSE(a == Unknown);
    ASSERT_FALSE(b == True);
    ASSERT_FALSE(b == False);
    ASSERT_FALSE(c == Unknown);
    ASSERT_FALSE(c == True);

    ASSERT_TRUE(True == a);
    ASSERT_TRUE(Unknown == b);
    ASSERT_TRUE(False == c);

    ASSERT_FALSE(False == a);
    ASSERT_FALSE(Unknown == a);
    ASSERT_FALSE(True == b);
    ASSERT_FALSE(False == b);
    ASSERT_FALSE(Unknown == c);
    ASSERT_FALSE(True == c);
}

TEST(class_trit, LogicAnd) {
    Trit a(True);
    Trit b(Unknown);
    Trit c(False);

    ASSERT_TRUE((a & b) == Trit(Unknown));
    ASSERT_TRUE((b & a) == Trit(Unknown));
    ASSERT_TRUE((a & c) == Trit(False));
    ASSERT_TRUE((c & a) == Trit(False));
    ASSERT_TRUE((b & c) == Trit(False));
    ASSERT_TRUE((c & b) == Trit(False));
    ASSERT_TRUE((c & c) == Trit(False));
    ASSERT_TRUE((b & b) == Trit(Unknown));
    ASSERT_TRUE((a & a) == Trit(True));

    ASSERT_TRUE((a & Unknown) == Trit(Unknown));
    ASSERT_TRUE((a & False) == Trit(False));
    ASSERT_TRUE((b & False) == Trit(False));
    ASSERT_TRUE((a & True) == Trit(True));
    ASSERT_TRUE((b & Unknown) == Trit(Unknown));
    ASSERT_TRUE((b & True) == Trit(Unknown));
    ASSERT_TRUE((c & Unknown) == Trit(False));
    ASSERT_TRUE((c & True) == Trit(False));
    ASSERT_TRUE((c & False) == Trit(False));

    ASSERT_TRUE((Unknown & a) == Trit(Unknown));
    ASSERT_TRUE((False & a) == Trit(False));
    ASSERT_TRUE((False & b) == Trit(False));
    ASSERT_TRUE((True & a) == Trit(True));
    ASSERT_TRUE((Unknown & b) == Trit(Unknown));
    ASSERT_TRUE((True & b) == Trit(Unknown));
    ASSERT_TRUE((Unknown & c) == Trit(False));
    ASSERT_TRUE((True & c) == Trit(False));
    ASSERT_TRUE((False & c) == Trit(False));
}

TEST(class_trit, LogicOr) {
    Trit a(True);
    Trit b(Unknown);
    Trit c(False);

    ASSERT_TRUE((a | b) == Trit(True));
    ASSERT_TRUE((b | a) == Trit(True));
    ASSERT_TRUE((a | c) == Trit(True));
    ASSERT_TRUE((c | a) == Trit(True));
    ASSERT_TRUE((b | c) == Trit(Unknown));
    ASSERT_TRUE((c | b) == Trit(Unknown));
    ASSERT_TRUE((c | c) == Trit(False));
    ASSERT_TRUE((b | b) == Trit(Unknown));
    ASSERT_TRUE((a | a) == Trit(True));

    ASSERT_TRUE((a | Unknown) == Trit(True));
    ASSERT_TRUE((a | False) == Trit(True));
    ASSERT_TRUE((b | False) == Trit(Unknown));
    ASSERT_TRUE((a | True) == Trit(True));
    ASSERT_TRUE((b | Unknown) == Trit(Unknown));
    ASSERT_TRUE((b | True) == Trit(True));
    ASSERT_TRUE((c | Unknown) == Trit(Unknown));
    ASSERT_TRUE((c | True) == Trit(True));
    ASSERT_TRUE((c | False) == Trit(False));

    ASSERT_TRUE((Unknown | a) == Trit(True));
    ASSERT_TRUE((False | a) == Trit(True));
    ASSERT_TRUE((False | b) == Trit(Unknown));
    ASSERT_TRUE((True | a) == Trit(True));
    ASSERT_TRUE((Unknown | b) == Trit(Unknown));
    ASSERT_TRUE((True | b) == Trit(True));
    ASSERT_TRUE((Unknown | c) == Trit(Unknown));
    ASSERT_TRUE((True | c) == Trit(True));
    ASSERT_TRUE((False | c) == Trit(False));
}

TEST(class_trit, logicNot) {
    Trit a(True);
    Trit b(Unknown);
    Trit c(False);

    ASSERT_TRUE((~a) == Trit(False));
    ASSERT_TRUE((~b) == Trit(Unknown));
    ASSERT_TRUE((~c) == Trit(True));
}

TEST(class_trit_set, constructor){
    TritSet set1;
    TritSet set2(10);
    ASSERT_TRUE(set1.capacity() == 0);
    ASSERT_TRUE(set2.capacity() == 10);
}

TEST(class_trit_set, setAt_and_getAt){
    TritSet set(32);
    set.setAt(5, True);
    set.setAt(3, False);
    set.setAt(4, Unknown);
    ASSERT_TRUE(set.getAt(4) == Unknown);
    ASSERT_TRUE(set.getAt(3) == False);
    ASSERT_TRUE(set.getAt(5) == True);
}



int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
