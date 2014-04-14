#ifndef USED_FAKES_H_ 
#define USED_FAKES_H_

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct Used_Fakes {
    long (*add)(long a, long b);
    long (*subtract)(long a, long b);
} Used_Fakes;

extern Used_Fakes sUsed_Fakes;

long Used_add_Dummy(long a, long b);
long Used_add_Stub(long a, long b);
long Used_add_Mock(long a, long b);
long Used_add_Real(long a, long b);

long Used_subtract_Dummy(long a, long b);
long Used_subtract_Stub(long a, long b);
long Used_subtract_Mock(long a, long b);
long Used_subtract_Real(long a, long b);

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif
