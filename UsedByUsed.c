/** Demonstrates how to handle calls to other C units
 *  from within the one that we compile with C++ linkage
 */

long UsedByUsed_plus(long a, long b) { return a + b; }
long UsedByUsed_minus(long a, long b) { return a - b; }
