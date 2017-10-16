#include "random.h"

static const size_t MIN_VALUE = 1;
static const size_t MAX_VALUE = 1000000;
static const size_t MIN_RANGE = 1;
static const size_t MAX_RANGE = 1000;


int rand(int min, int max)
{
    assert(min < max);
    return std::rand() % (max - min + 1) + min;
}


Interval Random::createInterval()
{
  const int low = rand(MIN_VALUE, MAX_VALUE);
  const int high = rand(low + int(MIN_RANGE), low + int(MAX_RANGE));
  return Interval(low, high);
}


IntervalVector Random::createIntervals(size_t treeSize)
{
    IntervalVector intervals;
    intervals.reserve(treeSize);

    while (intervals.size() < treeSize) {
        const Interval &interval = createInterval();
        if (intervals.cend() == std::find(intervals.cbegin(), intervals.cend(), interval)) {
            intervals.push_back(interval);
        }
    }

    return intervals;
}


IntervalTree Random::createTree(size_t treeSize)
{
    return IntervalTree(createIntervals(treeSize));
}
