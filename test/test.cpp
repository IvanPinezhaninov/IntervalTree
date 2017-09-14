#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "common.h"


TEST_CASE("Intervals with the same boundaries and different values")
{
    IntervalVector intervals
    {
        { 1, 2, 1 },
        { 1, 2, 2 }
    };

    IntervalTree intervalTree;

    for (auto interval : intervals) {
        REQUIRE(intervalTree.insert(interval));
    }

    for (auto interval : intervals) {
        REQUIRE_FALSE(intervalTree.insert(interval));
    }

    auto treeIntervals = intervalTree.intervals();

    REQUIRE_FALSE(treeIntervals.empty());
    REQUIRE(std::is_permutation(treeIntervals.cbegin(), treeIntervals.cend(), intervals.cbegin()));
}
