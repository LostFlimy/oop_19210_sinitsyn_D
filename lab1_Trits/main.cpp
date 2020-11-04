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
    ASSERT_TRUE(set2.getAt(5) == Unknown);
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

TEST(class_trit_set, assigment_operator){
    TritSet set1(30);
    TritSet set2(20);
    set1.setAt(1, True);
    set1.setAt(2, False);
    set1.setAt(6, True);
    set1.setAt(15, False);
    set1.setAt(17, True);
    set2.setAt(1, True);
    set2.setAt(2, True);
    set2.setAt(6, False);
    set2.setAt(15, Unknown);
    set2.setAt(13, Unknown);
    set1 = set2;
    ASSERT_TRUE(set1.capacity() == 20);
    ASSERT_TRUE(set1.getAt(1) == True);
    ASSERT_TRUE(set1.getAt(2) == True);
    ASSERT_TRUE(set1.getAt(6) == False);
    ASSERT_TRUE(set1.getAt(13) == Unknown);
    ASSERT_TRUE(set1.getAt(15) == Unknown);
    ASSERT_TRUE(set1.getAt(17) == Unknown);
}

TEST(class_trit_set, index_operator){
    TritSet set1(30);
    set1.setAt(1, True);
    set1.setAt(2, False);
    set1.setAt(6, True);
    set1.setAt(15, False);
    set1.setAt(17, True);
    ASSERT_TRUE(set1[1] == True);
    ASSERT_TRUE(set1[2] == False);
    ASSERT_TRUE(set1[3] == Unknown);
    ASSERT_TRUE(set1[6] == True);
    ASSERT_TRUE(set1[17] == True);
    ASSERT_TRUE(set1[0] == Unknown);
    set1[2] = True;
    set1[3] = False;
    set1[17] = Unknown;
    ASSERT_TRUE(set1[2] == True);
    ASSERT_TRUE(set1[3] == False);
    ASSERT_TRUE(set1[17] == Unknown);
    set1[2] = set1[2] & False;
    ASSERT_TRUE(set1[2] == False);
    set1[2] = True | set1[2];
    ASSERT_TRUE(set1[2] == True);
    set1[2] = False & set1[2];
    ASSERT_TRUE(set1[2] == False);
    set1[2] = set1[2] | True;
    ASSERT_TRUE(set1[2] == True);
}

TEST(class_trit_set, memory_check){
    TritSet set(20);
    set[19] = False;
    set[100] = Unknown;
    cout << set[120];
    ASSERT_TRUE(set.capacity() == 20);
    ASSERT_TRUE(set.size_cells() == 2);
    set[40] = True;
    ASSERT_TRUE(set.capacity() == 41);
    ASSERT_TRUE(set.size_cells() == 3);
    set[50] = False;
    ASSERT_TRUE(set.capacity() == 51);
    ASSERT_TRUE(set.size_cells() == 4);
}

TEST(class_trit_set, logic_operations){
    TritSet set1(6);
    TritSet set2(7);
    set1[0] = True;
    set1[1] = False;
    set1[2] = Unknown;
    set1[3] = True;
    set1[4] = Unknown;
    set1[5] = False;
    set2[0] = True;
    set2[1] = True;
    set2[2] = True;
    set2[3] = False;
    set2[4] = False;
    set2[5] = False;
    set2[6] = True;

    TritSet setand = set1 & set2;
    ASSERT_TRUE(setand[0] == True);
    ASSERT_TRUE(setand[1] == False);
    ASSERT_TRUE(setand[2] == Unknown);
    ASSERT_TRUE(setand[3] == False);
    ASSERT_TRUE(setand[4] == False);
    ASSERT_TRUE(setand[5] == False);
    ASSERT_TRUE(setand.size_cells() == 1);
    ASSERT_TRUE(setand.capacity() == 6);

    TritSet setor = set1 | set2;
    ASSERT_TRUE(setor[0] == True);
    ASSERT_TRUE(setor[1] == True);
    ASSERT_TRUE(setor[2] == True);
    ASSERT_TRUE(setor[3] == True);
    ASSERT_TRUE(setor[4] == Unknown);
    ASSERT_TRUE(setor[5] == False);
    ASSERT_TRUE(setor[6] == True);
    ASSERT_TRUE(setor.capacity() == 7);
    ASSERT_TRUE(setor.size_cells() == 1);

    TritSet setnot = ~set1;
    ASSERT_TRUE(setnot[0] == False);
    ASSERT_TRUE(setnot[1] == True);
    ASSERT_TRUE(setnot[2] == Unknown);
    ASSERT_TRUE(setnot[3] == False);
    ASSERT_TRUE(setnot[4] == Unknown);
    ASSERT_TRUE(setnot[5] == True);
    ASSERT_TRUE(setnot.size_cells() == 1);
    ASSERT_TRUE(setnot.capacity() == 6);
    TritSet set3(50);
    setand = set1 & set3;
    setor = set1 | set3;
    setnot = ~set3;
    ASSERT_TRUE(setand.capacity() == 6);
    ASSERT_TRUE(setand.size_cells() == 1);
    ASSERT_TRUE(setor.capacity() == 50);
    ASSERT_TRUE(setor.size_cells() == 4);
    ASSERT_TRUE(setnot.size_cells() == 4);
    ASSERT_TRUE(setnot.capacity() == 50);
}

TEST(class_trit_set, shrink){
    TritSet set(100);
    set[40] = Unknown;
    set.shrink();
    ASSERT_TRUE(set.capacity() == 100);
    ASSERT_TRUE(set.size_cells() == 7);
    set[20] = True;
    set[30] = False;
    set.shrink();
    ASSERT_TRUE(set.capacity() == 31);
    ASSERT_TRUE(set.size_cells() == 2);
}

TEST(class_trit_set, length){
    TritSet set(100);
    set[20] = Unknown;
    ASSERT_TRUE(set.length() == -1);
    set[30] = True;
    ASSERT_TRUE(set.length() == 31);
    set[10] = False;
    ASSERT_TRUE(set.length() == 31);
    set[120] = True;
    ASSERT_TRUE(set.length() == 121);
}

TEST(class_trit_set, trim){
    TritSet set(20);
    set[15] = True;
    set[10] = False;
    set.trim(11);
    ASSERT_TRUE(set[15] == Unknown);
    ASSERT_TRUE(set.capacity() == 20);
    ASSERT_TRUE(set.length() == 11);
    set[18] = True;
    set[11] = False;
    set.trim(10);
    ASSERT_TRUE(set[18] == Unknown);
    ASSERT_TRUE(set[11] == Unknown);
    ASSERT_TRUE(set.length() == -1);
    ASSERT_TRUE(set.capacity() == 20);
}

TEST(class_trit_set, cardinality){
    TritSet set(20);
    set[0] = True;
    set[1] = True;
    set[16] = True;
    set[3] = False;
    set[17] = Unknown;
    set[14] = False;
    ASSERT_TRUE(set.cardinality(True) == 3);
    ASSERT_TRUE(set.cardinality(False) == 2);
    ASSERT_TRUE(set.cardinality(Unknown) == 13);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
