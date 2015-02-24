#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C" {
    #include "Used.h"
    #include "User.h"
}

#include "Used_Fakes.h"

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
        UT_PTR_SET(sUsed_Fakes.add, C::Used_add);
        UT_PTR_SET(sUsed_Fakes.subtract, C::Used_subtract);
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
        UT_PTR_SET(sUsed_Fakes.add, C::Used_add);
        UT_PTR_SET(sUsed_Fakes.subtract, C::Used_subtract);
    }
};
TEST(User_withUsedRealCode, calculate) {
    LONGS_EQUAL(-141, User_calculate(57, 312));
}

TEST_GROUP(User_withUsedStubCode) {
    void setup() {
        UT_PTR_SET(sUsed_Fakes.add, Stub::Used_add_Stub);
        UT_PTR_SET(sUsed_Fakes.subtract, Stub::Used_subtract_Stub);
    }
};
TEST(User_withUsedStubCode, calculate) {
    LONGS_EQUAL(-141, User_calculate(57, 312));
}

TEST_GROUP(User_withUsedMockCode) {
    void setup() {
        UT_PTR_SET(sUsed_Fakes.add, Mock::Used_add_Mock);
        UT_PTR_SET(sUsed_Fakes.subtract, Mock::Used_subtract_Mock);
    }
    void teardown() {
        mock().clear();
    }
};
TEST(User_withUsedMockCode, calculate) {
    mock().expectOneCall("Used_add")
          .withParameter("a", 57)
          .withParameter("b", 57)
          .andReturnValue(114);
    mock().expectOneCall("Used_subtract")
          .withParameter("a", 312)
          .withParameter("b", 57)
          .andReturnValue(255);
    mock().expectOneCall("Used_subtract")
          .withParameter("a", 114)
          .withParameter("b", 255)
          .andReturnValue(-141);
    LONGS_EQUAL(-141, User_calculate(57, 312));
    mock().checkExpectations();
}

TEST_GROUP(User_withUsedMixed) {
    void setup() {
        UT_PTR_SET(sUsed_Fakes.add, Stub::Used_add_Stub);
        UT_PTR_SET(sUsed_Fakes.subtract, Mock::Used_subtract_Mock);
    }
    void teardown() {
        mock().clear();
    }
};
TEST(User_withUsedMixed, calculate) {
    mock().expectOneCall("Used_subtract")
          .withParameter("a", 312)
          .withParameter("b", 57)
          .andReturnValue(255);
    mock().expectOneCall("Used_subtract")
          .withParameter("a", 114)
          .withParameter("b", 255)
          .andReturnValue(-141);
    LONGS_EQUAL(-141, User_calculate(57, 312));
}

int main(int ac, char** av)
{
	return CommandLineTestRunner::RunAllTests(ac, av);
}

