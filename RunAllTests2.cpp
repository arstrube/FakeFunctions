#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

/// C production code /////////////////////////////////////
namespace C {
    long Used_add(long a, long b) { return a + b; }
    long Used_subtract(long a, long b) { return a - b; }
}

/// Dummies ///////////////////////////////////////////////
struct Used {
    virtual long add(long, long) { return 0l; }
    virtual long subtract(long, long) { return 0l; }
};

struct Used_Real : public Used {
    virtual long add(long a, long b) override {
        return C::Used_add(a, b);
    }
    virtual long subtract(long a, long b) override {
        return C::Used_subtract(a, b);
    }
};

struct Used_Mock : public Used {
    virtual long add(long a, long b) override {
        mock().actualCall("Used_add")
             .withParameter("a", a)
             .withParameter("b", b);
        return mock().returnValue().getLongIntValue();
    }
    virtual long subtract(long a, long b) override {
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

static Used_Real used_real;
static Used used_dummy;
static Used_Stub used_stub;
static Used_Mock used_mock;
static Used *used = &used_dummy;

/// Fake proxies called by production code ///////////////
extern "C" long Used_add(long a, long b) {
    return used->add(a, b);
}

extern "C" long Used_subtract(long a, long b) {
    return used->subtract(a, b);
}

/// C production code /////////////////////////////////////

extern "C"  long User_calculate(long a, long b) {
        long temp1 = Used_add(a, a);
        long temp2 = Used_subtract(b, a);
        return Used_subtract(temp1, temp2);
}

/// Tests /////////////////////////////////////////////////
TEST_GROUP(Used_withReal){
    void setup() override {
        UT_PTR_SET(used, &used_real);
    }
}; 
TEST(Used_withReal, add) {
    LONGS_EQUAL(5678, Used_add(5555, 123));
}
TEST(Used_withReal, subtract) {
    LONGS_EQUAL(1, Used_subtract(-34567, -34568));
}

TEST_GROUP(Used_withDummy) {}; 
TEST(Used_withDummy, add) {
    LONGS_EQUAL(0, Used_add(5555, 123));
}
TEST(Used_withDummy, subtract) {
    LONGS_EQUAL(0, Used_subtract(-34567, -34568));
}

TEST_GROUP(User_withUsedStubCode) {
    void setup() override {
        UT_PTR_SET(used, &used_stub);
    }
};
TEST(User_withUsedStubCode, calculate) {
    LONGS_EQUAL(-141, User_calculate(57, 312));
}

TEST_GROUP(User_withUsedMockCode) {
    void setup() override {
        UT_PTR_SET(used, &used_mock);
    }
    void teardown() {
        mock().clear();
        mock().checkExpectations();
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
}

/// CppUTest main() ///////////////////////////////////////
int main(int ac, char** av)
{
	return RUN_ALL_TESTS(ac, av);
}

