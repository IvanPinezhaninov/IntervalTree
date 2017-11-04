#ifndef TEST_RANDOM_H
#define TEST_RANDOM_H

#include "common.h"


namespace Random {

void setRndGeneratorSeed(uint64_t seed);

Interval createInterval();

IntervalVector createIntervals(size_t treeSize);

IntervalTree createTree(size_t treeSize);

} // namespace Rand

#endif // TEST_RANDOM_H
