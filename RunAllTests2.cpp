#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C" {
    
/// C production code /////////////////////////////////////
long Used_add(long a, long b);
long Used_subtract(long a, long b);

long User_calculate(long a, long b) {
    long temp1 = Used_add(a, a);
    long temp2 = Used_subtract(b, a);
    return Used_subtract(temp1, temp2);
}

/// Dummies ///////////////////////////////////////////////
struct Used {
    virtual long add(long, long) { return 0l; }
    virtual long subtract(long, long) { return 0l; }
};

struct Used_Mock : public Used {
    virtual long add(long a, long b) override {
        mock().actualCall("Used_add")
             .withParameter("a", a)
             .withParameter("b", b);
        return mock().returnValue().getLongIntValue();
    }
    virtual long Used_subtract_Mock(long a, long b) {
        mock().actualCall("Used_subtract")
             .withParameter("a", a)
             .withParameter("b", b);
        return mock().returnValue().getLongIntValue();
    }
};

#include <cstdio>
struct Used_Stub : public Used {
    virtual long add(long a, long b) override {
        printf("\n    Used_add(%ld, %ld) was called\n", a, b);
        fflush(stdout);
        return a + b;
    }
    virtual long subtract(long a, long b) override {
        printf("\n    Used_subtract(%ld, %ld) was called\n", a, b);
        fflush(stdout);
        return a - b;
    }
};

static Used used;

/// Fake proxies called by production code ///////////////
long Used_add(long a, long b) {
    return used.add(a, b);
}
long Used_subtract(long a, long b) {
    return used.subtract(a, b);
}

} // extern "C"

/// Tests /////////////////////////////////////////////////
TEST_GROUP(Used_withDummy) {}; 
TEST(Used_withDummy, add) {
    LONGS_EQUAL(0, Used_add(5555, 123));
}
TEST(Used_withDummy, subtract) {
    LONGS_EQUAL(0, Used_subtract(-34567, -34568));
}

TEST_GROUP(User_withUsedStubCode) {
    void setup() override {
//        UT_PTR_SET(sUsed_Fakes.add, Used_add_Stub);
//        UT_PTR_SET(sUsed_Fakes.subtract, Used_subtract_Stub);
    }
};
TEST(User_withUsedStubCode, calculate) {
    LONGS_EQUAL(-141, User_calculate(57, 312));
}

TEST_GROUP(User_withUsedMockCode) {
    void setup() override {
//        UT_PTR_SET(sUsed_Fakes.add, Used_add_Mock);
 //       UT_PTR_SET(sUsed_Fakes.subtract, Used_subtract_Mock);
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
    void setup() override {
//        UT_PTR_SET(sUsed_Fakes.add, Used_add_Stub);
//        UT_PTR_SET(sUsed_Fakes.subtract, Used_subtract_Mock);
    }
    void teardown() override {
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

/// CppUTest main() ///////////////////////////////////////
int main(int ac, char** av)
{
	return RUN_ALL_TESTS(ac, av);
}

