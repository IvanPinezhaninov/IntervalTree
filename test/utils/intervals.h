#ifndef TEST_INTERVALS_H
#define TEST_INTERVALS_H

#include "common.h"


namespace Test {

Interval interval();

IntervalVector innerIntervals();

IntervalVector outerIntervals();

IntervalVector leftIntervals();

IntervalVector rightIntervals();

IntervalVector leftOverlappingIntervals();

IntervalVector rightOverlappingIntervals();

IntervalVector boundaryIntervals();

IntervalVector leftBoundaryIntervals();

IntervalVector rightBoundaryIntervals();

IntervalVector compositeIntervals(const IntervalVector &a, const IntervalVector &b);

} // namespace Test

#endif // TEST_INTERVALS_H
