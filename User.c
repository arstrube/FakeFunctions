#include "User.h"
#include "Used.h"

unsigned long User_multiply(unsigned long a, unsigned long b) {
    unsigned long i, tmp = 0;
    for (i=0; i<=b; i++) tmp = Used_add(tmp, a);
    return Used_subtract(tmp, a); /// this is on purpose!
}
