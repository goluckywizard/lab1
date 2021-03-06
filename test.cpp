#include "Tritset.h"
#include "gtest/gtest.h"
TEST(Tritset_Test,base) {
    Tritset set(1000);
    size_t allocLength = set.capacity();
    ASSERT_TRUE(allocLength >= 1000*2 / 8 / sizeof(unsigned int) );
    set[1000000000] = Unknown;
    ASSERT_TRUE(allocLength == set.capacity());

    if(set[2000000000]==True){}
    ASSERT_TRUE(allocLength == set.capacity());

    set[1000000000] = True;
    ASSERT_TRUE(allocLength < set.capacity());

    allocLength = set.capacity();
    set[1000000000] = Unknown;
    set[1000000] = False;
    ASSERT_TRUE(allocLength == set.capacity());
    set.shrink();
    ASSERT_TRUE(allocLength > set.capacity());
    Tritset setA(1000);
    Tritset setB(2000);
    Tritset setC = setA & setB;
    ASSERT_TRUE(setC.capacity() == setB.capacity());
}
TEST (Tritset_Test, capacity_test) {
    Tritset set(16);
    EXPECT_EQ (set.capacity(), 16*2 / 8 / sizeof(unsigned int));
    Tritset set1(2000);
    EXPECT_EQ (set1.capacity(), 2000*2 / 8 / sizeof(unsigned int));
    Tritset set2(1000);
    EXPECT_EQ (set2.capacity(), 1000*2 / 8 / sizeof(unsigned int) + 1);
    set[2000] = True;
    EXPECT_EQ (set.capacity(), 2000*2 / 8 / sizeof(unsigned int) + 1);
    set[2000] = Unknown;
    set.shrink();
    EXPECT_EQ (set.capacity(), 16*2 / 8 / sizeof(unsigned int));
}
TEST (Tritset_Test, length_test) {
    Tritset set(10);
    EXPECT_EQ(set.length(), 0);
    set[20] = True;
    EXPECT_EQ(set.length(), 21);
    set[30] = False;
    EXPECT_EQ(set.length(), 31);
    set[40] = Unknown;
    EXPECT_EQ(set.length(), 31);
    set[40] = True;
    EXPECT_EQ(set.length(), 41);
    set[40] = Unknown; set[30] = Unknown;
    EXPECT_EQ(set.length(), 21);
    set[20] = Unknown;
    EXPECT_EQ(set.length(), 0);
    set[40] = True;
    set.trim(20);
    EXPECT_EQ(set.length(), 0);
}
TEST (Tritset_Test, trim_test) {
    Tritset set(10);
    EXPECT_EQ(set.capacity(), 1);
    set.trim(5);
    EXPECT_EQ(set.capacity(), 1);
    set.trim(5000);
    EXPECT_EQ(set.capacity(), 1);
    Tritset set1(2000);
    EXPECT_EQ(set1.capacity(), 2000*2 / 8 / sizeof(unsigned int));
    set1.trim(16);
    EXPECT_EQ(set1.capacity(), 1);
}
TEST (Tritset_Test, cardinality_test) {
    Tritset set(20);
    EXPECT_EQ(set.cardinality(True), 0);
    EXPECT_EQ(set.cardinality(False), 0);
    EXPECT_EQ(set.cardinality(Unknown), 0);
    set[10] = True;
    EXPECT_EQ(set.cardinality(True), 1);
    EXPECT_EQ(set.cardinality(False), 0);
    EXPECT_EQ(set.cardinality(Unknown), 10);
    set[30] = False;
    EXPECT_EQ(set.cardinality(True), 1);
    EXPECT_EQ(set.cardinality(False), 1);
    EXPECT_EQ(set.cardinality(Unknown), 29);
    Tritset set1("TUFTUFFUTFUT");
    EXPECT_EQ(set1.cardinality(True), 4);
    EXPECT_EQ(set1.cardinality(False), 4);
    EXPECT_EQ(set1.cardinality(Unknown), 4);
}
TEST (Tritset_Test, map_cardinality_test) {
    Tritset set(20);
    EXPECT_EQ(set.cardinality()[True], 0);
    EXPECT_EQ(set.cardinality()[False], 0);
    EXPECT_EQ(set.cardinality()[Unknown], 0);
    set[10] = True;
    EXPECT_EQ(set.cardinality()[True], 1);
    EXPECT_EQ(set.cardinality()[False], 0);
    EXPECT_EQ(set.cardinality()[Unknown], 10);
    set[30] = False;
    EXPECT_EQ(set.cardinality()[True], 1);
    EXPECT_EQ(set.cardinality()[False], 1);
    EXPECT_EQ(set.cardinality()[Unknown], 29);
    Tritset set1("TUFTUFFUTFUT");
    EXPECT_EQ(set1.cardinality()[True], 4);
    EXPECT_EQ(set1.cardinality()[False], 4);
    EXPECT_EQ(set1.cardinality()[Unknown], 4);
}
TEST (Tritset_Test, AND_test) {
    Tritset A("TTTUUUFFF");
    Tritset B("TUFTUFTUF");
    Tritset C(10);
    C = (A & B);
    EXPECT_EQ(C.length(), 9);
    EXPECT_TRUE(C[0] == True);
    EXPECT_TRUE(C[1] == Unknown);
    EXPECT_TRUE(C[2] == False);
    EXPECT_TRUE(C[3] == Unknown);
    EXPECT_TRUE(C[4] == Unknown);
    EXPECT_TRUE(C[5] == False);
    EXPECT_TRUE(C[6] == False);
    EXPECT_TRUE(C[7] == False);
    EXPECT_TRUE(C[8] == False);
    Tritset setA(20), setB(30), setC(1);
    setC = setA & setB;
    EXPECT_EQ(setC.capacity(), 30 * 2 / 8 / sizeof(unsigned int) + 1);
}
TEST (Tritset_Test, OR_test) {
    Tritset A("TTTUUUFFF");
    Tritset B("TUFTUFTUF");
    Tritset C(10);
    C = A | B;
    EXPECT_EQ(C.length(), 9);
    EXPECT_TRUE(C[0] == True);
    EXPECT_TRUE(C[1] == True);
    EXPECT_TRUE(C[2] == True);
    EXPECT_TRUE(C[3] == True);
    EXPECT_TRUE(C[4] == Unknown);
    EXPECT_TRUE(C[5] == Unknown);
    EXPECT_TRUE(C[6] == True);
    EXPECT_TRUE(C[7] == Unknown);
    EXPECT_TRUE(C[8] == False);
    Tritset setA(20), setB(30), setC(1);
    setC = setA | setB;
    EXPECT_EQ(setC.capacity(), 30 * 2 / 8 / sizeof(unsigned int) + 1);
}
TEST (Tritset_Test, NOT_test) {
    Tritset A("TUF");
    Tritset C(10);
    C = (!A);
    EXPECT_EQ(C.length(), 3);
    EXPECT_TRUE(C[0] == False);
    EXPECT_TRUE(C[1] == Unknown);
    EXPECT_TRUE(C[2] == True);
}
TEST (Tritset_Test, shrink_test) {
    Tritset set(2000);
    EXPECT_EQ(set.capacity(), 2000 / 4 / sizeof(unsigned int));
    set[1000] = True;
    EXPECT_EQ(set.capacity(), 2000 / 4 / sizeof(unsigned int));
    set.shrink();
    EXPECT_EQ(set.capacity(), 2000 / 4 / sizeof(unsigned int));
    set[3000] = True;
    EXPECT_EQ(set.capacity(), 3000 / 4 / sizeof(unsigned int) + 1);
    set[3000] = Unknown;
    set.shrink();
    EXPECT_EQ(set.capacity(), 2000 / 4 / sizeof(unsigned int));
}
TEST (Tritset_Test, forauto) {
    Tritset A("TTTTTTTTTT");
    for (auto item : A) {
        EXPECT_TRUE(item == True);
    }
    Tritset B("FFFFFFFFFF");
    Tritset C = A & B;
    for (auto item : C) {
        EXPECT_TRUE(item == False);
    }
}
int testes() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
