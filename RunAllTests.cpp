#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C" {
    #include "User.h"
}

#include "Used_Fake.h"

TEST_GROUP(Used_withDummy) {
}; 
TEST(Used_withDummy, add) {
    LONGS_EQUAL(0, Used_add(5555, 123));
}
TEST(Used_withDummy, subtract) {
    LONGS_EQUAL(0, Used_subtract(-34567, -34568));
}

TEST_GROUP(Used_withRealCode) {
    void setup() {
        UT_PTR_SET(Used_Fake::add, C::Used_add);
        UT_PTR_SET(Used_Fake::subtract, C::Used_subtract);
    }
};
TEST(Used_withRealCode, add) {
    LONGS_EQUAL(5678, Used_add(5555, 123));
}
TEST(Used_withRealCode, subtract) {
    LONGS_EQUAL(1, Used_subtract(-34567, -34568));
}

TEST_GROUP(User_withUsedRealCode) {
    void setup() {
        UT_PTR_SET(Used_Fake::add, C::Used_add);
        UT_PTR_SET(Used_Fake::subtract, C::Used_subtract);
    }
};
TEST(User_withUsedRealCode, multiply) {
    LONGS_EQUAL(1000000, User_multiply(200000, 5));
}

TEST_GROUP(User_withUsedStubCode) {
    void setup() {
        UT_PTR_SET(Used_Fake::add, Stub::Used_add_Stub);
        UT_PTR_SET(Used_Fake::subtract, Stub::Used_subtract_Stub);
    }
};
TEST(User_withUsedStubCode, multiply) {
    LONGS_EQUAL(330000, User_multiply(110000, 3));
}

TEST_GROUP(User_withUsedMockCode) {
    void setup() {
        UT_PTR_SET(Used_Fake::add, Mock::Used_add_Mock);
        UT_PTR_SET(Used_Fake::subtract, Mock::Used_subtract_Mock);
    }
    void teardown() {
        mock().clear();
    }
};
TEST(User_withUsedMockCode, calculate) {
    mock().expectOneCall("Used_add")
          .withParameter("a", 0).withParameter("b", 3).andReturnValue(3);
    mock().expectOneCall("Used_add")
          .withParameter("a", 3).withParameter("b", 3).andReturnValue(6);
    mock().expectOneCall("Used_add")
          .withParameter("a", 6).withParameter("b", 3).andReturnValue(9);
    mock().expectOneCall("Used_add")
          .withParameter("a", 9).withParameter("b", 3).andReturnValue(12);
    mock().expectOneCall("Used_subtract")
          .withParameter("a", 12).withParameter("b", 3).andReturnValue(9);
    LONGS_EQUAL(9, User_multiply(3, 3));
    mock().checkExpectations();
}

TEST_GROUP(User_withUsedMixed) {
    void setup() {
        UT_PTR_SET(Used_Fake::add, Stub::Used_add_Stub);
        UT_PTR_SET(Used_Fake::subtract, Mock::Used_subtract_Mock);
    }
    void teardown() {
        mock().clear();
    }
};
TEST(User_withUsedMixed, multiply) {
    mock().expectOneCall("Used_subtract")
          .withParameter("a", 20)
          .withParameter("b", 5)
          .andReturnValue(15);
    LONGS_EQUAL(15, User_multiply(5, 3));
}

int main(int ac, char** av)
{
	return CommandLineTestRunner::RunAllTests(ac, av);
}

