/** For the test, do not link this file directly. */

#include "Used.h"
#include "UsedByUsed.h"

long Used_add(long a, long b) { return UsedByUsed_plus(a, b); }
long Used_subtract(long a, long b) { return UsedByUsed_minus(a, b); }
