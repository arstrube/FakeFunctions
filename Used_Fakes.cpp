#include "CppUTestExt/MockSupport.h"

/** Original code compiled here, within separate namespace
 *  Do not build the original code elsewhere !
 */
namespace C {
    #include "Used.c" /** C++ will mangle function names */
}

#include "Used_Fakes.h"

/** Dummy implementations
 */
namespace Dummy {
    long Used_add(long, long) { return 0L; }
    long Used_subtract(long, long) { return 0L; }
}

/** Struct to hold function pointers
 */
Used_Fakes sUsed_Fakes = {
    .add = Dummy::Used_add,
    .subtract = Dummy::Used_subtract,
};

/** Mock implementations
 */
namespace Mock {
    long Used_add_Mock(long a, long b) {
        mock().actualCall("Used_add")
              .withParameter("a", a)
              .withParameter("b", b);
        return mock().returnValue().getLongIntValue();
    }
    long Used_subtract_Mock(long a, long b) {
        mock().actualCall("Used_subtract")
              .withParameter("a", a)
              .withParameter("b", b);
        return mock().returnValue().getLongIntValue();
    }
}

/** Wrappers to be linked in place of original functions
 */
extern "C" long Used_add(long a, long b) {
    return sUsed_Fakes.add(a, b);
}
extern "C" long Used_subtract(long a, long b) {
    return sUsed_Fakes.subtract(a, b);
}

/** Mock implementations 
 *  printf / stdio only for demonstration!
 */
#include <cstdio>
namespace Stub {
    long Used_add_Stub(long a, long b) {
        printf("\n    Used_add(%ld, %ld) was called\n", a, b);
        return a + b;
    }
    long Used_subtract_Stub(long a, long b) {
        printf("\n    Used_subtract(%ld, %ld) was called\n", a, b);
        return a - b;
    }
}
