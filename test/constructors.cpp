#include "catch.hpp"
#include "common.h"

#include <list>
#include <set>

using IntervalList = std::list<Interval>;
using IntervalSet = std::set<Interval>;


TEST_CASE("Constructor for list container")
{
    IntervalList intervals
    {
        { 1, 2 },
        { 3, 4 }
    };

    IntervalTree intervalTree(intervals);

    auto treeIntervals = intervalTree.intervals();

    REQUIRE_FALSE(treeIntervals.empty());
    REQUIRE(std::is_permutation(treeIntervals.cbegin(), treeIntervals.cend(), intervals.cbegin()));
}


TEST_CASE("Constructor for set container")
{
    IntervalSet intervals
    {
        { 1, 2 },
        { 3, 4 }
    };

    IntervalTree intervalTree(intervals);

    auto treeIntervals = intervalTree.intervals();

    REQUIRE_FALSE(treeIntervals.empty());
    REQUIRE(std::is_permutation(treeIntervals.cbegin(), treeIntervals.cend(), intervals.cbegin()));
}


TEST_CASE("Constructor for vector container")
{
    IntervalVector intervals
    {
        { 1, 2 },
        { 3, 4 }
    };

    IntervalTree intervalTree(intervals);

    auto treeIntervals = intervalTree.intervals();

    REQUIRE_FALSE(treeIntervals.empty());
    REQUIRE(std::is_permutation(treeIntervals.cbegin(), treeIntervals.cend(), intervals.cbegin()));
}


TEST_CASE("Constructor for list container iterators")
{
    IntervalList intervals
    {
        { 1, 2 },
        { 3, 4 }
    };

    IntervalTree intervalTree(intervals.begin(), intervals.end());

    auto treeIntervals = intervalTree.intervals();

    REQUIRE_FALSE(treeIntervals.empty());
    REQUIRE(std::is_permutation(treeIntervals.cbegin(), treeIntervals.cend(), intervals.cbegin()));
}


TEST_CASE("Constructor for set container iterators")
{
    IntervalSet intervals
    {
        { 1, 2 },
        { 3, 4 }
    };

    IntervalTree intervalTree(intervals.begin(), intervals.end());

    auto treeIntervals = intervalTree.intervals();

    REQUIRE_FALSE(treeIntervals.empty());
    REQUIRE(std::is_permutation(treeIntervals.cbegin(), treeIntervals.cend(), intervals.cbegin()));
}


TEST_CASE("Constructor for vector container iterators")
{
    IntervalVector intervals
    {
        { 1, 2 },
        { 3, 4 }
    };

    IntervalTree intervalTree(intervals.begin(), intervals.end());

    auto treeIntervals = intervalTree.intervals();

    REQUIRE_FALSE(treeIntervals.empty());
    REQUIRE(std::is_permutation(treeIntervals.cbegin(), treeIntervals.cend(), intervals.cbegin()));
}
