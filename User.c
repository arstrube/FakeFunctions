#include "User.h"
#include "Used.h"

long User_calculate(long a, long b) {
    long temp1 = Used_add(a, a);
    long temp2 = Used_subtract(b, a);
    return Used_subtract(temp1, temp2);
}
