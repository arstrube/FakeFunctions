#include "Used.c" /** C++ will mangle function names */
#include "Used_Fakes.h"

extern "C" long Used_add_Real(long a, long b)
{
    return Used_add(a, b);
}

extern "C" long Used_subtract_Real(long a, long b)
{
    return Used_subtract(a, b);
}
