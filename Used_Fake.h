#ifndef USED_FAKES_H_ 
#define USED_FAKES_H_

extern "C" {
    #include "UsedByUsed.h" /// Ensure C linkage
    #include "used.h"
}

struct Used_Fake {
    static long (*add)(long a, long b);
    static long (*subtract)(long a, long b);
};

namespace Dummy {
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

namespace C {
    long Used_add(long a, long b);
    long Used_subtract(long a, long b);
}

#endif
