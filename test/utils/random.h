#ifndef TEST_RANDOM_H
#define TEST_RANDOM_H

#include "common.h"


namespace Random {

Interval createInterval();

IntervalVector createIntervals(size_t treeSize);

IntervalTree createTree(const IntervalVector &intervals);

IntervalTree createTree(size_t treeSize);

} // namespace Rand

#endif // TEST_RANDOM_H
