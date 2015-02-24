#ifndef USED_FAKES_H_ 
#define USED_FAKES_H_

typedef struct Used_Fakes {
    long (*add)(long a, long b);
    long (*subtract)(long a, long b);
} Used_Fakes;

extern Used_Fakes sUsed_Fakes;

namespace Dummy{
    long Used_add(long a, long b);
    long Used_subtract(long a, long b);
}

namespace C {
    long Used_add(long a, long b);
    long Used_subtract(long a, long b);
}

namespace Mock {
    long Used_add_Mock(long a, long b);
    long Used_subtract_Mock(long a, long b);
}

namespace Stub {
    long Used_add_Stub(long a, long b);
    long Used_subtract_Stub(long a, long b);
}

#endif
