#include "CppUTestExt/MockSupport.h"

#include "Used_Fake.h"

namespace Dummy {
    long Used_add(long, long) { return 0L; }
    long Used_subtract(long, long) { return 0L; }
}

#include <cstdio>
namespace Stub {
    long Used_add(long a, long b) {
        printf("\n    Used_add(%ld, %ld) was called\n", a, b);
        return a + b;
    }
    long Used_subtract(long a, long b) {
        printf("\n    Used_subtract(%ld, %ld) was called\n", a, b);
        return a - b;
    }
}

namespace Mock {
    long Used_add(long a, long b) {
        mock().actualCall("Used_add")
              .withParameter("a", a).withParameter("b", b);
        return mock().returnValue().getLongIntValue();
    }
    long Used_subtract(long a, long b) {
        mock().actualCall("Used_subtract")
              .withParameter("a", a).withParameter("b", b);
        return mock().returnValue().getLongIntValue();
    }
}

/** Original C code -- do not build elsewhere !
 */
namespace C {
    #include "Used.c" /** C++ will mangle function names */
}

/** Initialization of function pointers
 */
long (*Used_Fake::add)(long a, long b) = Dummy::Used_add;
long (*Used_Fake::subtract)(long a, long b) = Dummy::Used_subtract;

/** Wrappers to be linked in place of original functions
 */
extern "C" long Used_add(long a, long b) {
    return Used_Fake::add(a, b);
}
extern "C" long Used_subtract(long a, long b) {
    return Used_Fake::subtract(a, b);
}
