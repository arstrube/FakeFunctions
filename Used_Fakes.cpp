extern "C" {
    
#include "Used.h"
#include "Used_Fakes.h"
#include "CppUTestExt/MockSupport_c.h"

long Used_add_Dummy(long, long) { return 0L; }
long Used_subtract_Dummy(long, long) { return 0L; }

Used_Fakes sUsed_Fakes = {
    .add = Used_add_Dummy,
    .subtract = Used_subtract_Dummy,
};

long Used_add_Mock(long a, long b) {
    mock_c()->actualCall("Used_add")
            ->withIntParameters("a", a)
            ->withIntParameters("b", b);
    return (long) mock_c()->returnValue().value.intValue;
}
long Used_subtract_Mock(long a, long b) {
    mock_c()->actualCall("Used_subtract")
            ->withIntParameters("a", a)
            ->withIntParameters("b", b);
    return (long) mock_c()->returnValue().value.intValue;
}

long Used_add(long a, long b) {
    return sUsed_Fakes.add(a, b);
}
long Used_subtract(long a, long b) {
    return sUsed_Fakes.subtract(a, b);
}

#include <cstdio>

long Used_add_Stub(long a, long b) {
    printf("Used_add(%ld, %ld) was called\n", a, b);
    return a + b;
}
long Used_subtract_Stub(long a, long b) {
    printf("Used_subtract(%ld, %ld) was called\n", a, b);
    return a - b;
}

}
