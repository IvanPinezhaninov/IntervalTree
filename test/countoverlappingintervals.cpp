#include "catch.hpp"
#include "intervals.h"


TEST_CASE("Count overlapping intervals")
{
    SECTION("Empty tree")
    {
        const IntervalTree tree;
        const auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(tree.isEmpty());
        REQUIRE(0 == count);
    }


    SECTION("Boundary interval")
    {
        const auto tree = IntervalTree(Test::boundaryIntervals());
        const auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == Test::boundaryIntervals().size());
    }


    SECTION("Outer intervals")
    {
        const auto intervals = Test::outerIntervals();
        const auto tree = IntervalTree(intervals);
        const auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }


    SECTION("Outer and boundary intervals")
    {
        const auto intervals = Test::compositeIntervals(Test::outerIntervals(), Test::boundaryIntervals());
        const auto tree = IntervalTree(intervals);
        const auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }


    SECTION("Inner intervals")
    {
        const auto tree = IntervalTree(Test::innerIntervals());
        const auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == Test::innerIntervals().size());
    }


    SECTION("Inner and boundary intervals")
    {
        const auto intervals = Test::compositeIntervals(Test::innerIntervals(), Test::boundaryIntervals());
        const auto tree = IntervalTree(intervals);
        const auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }


    SECTION("Outer and inner intervals")
    {
        const auto intervals = Test::compositeIntervals(Test::outerIntervals(), Test::innerIntervals());
        const auto tree = IntervalTree(intervals);
        const auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }


    SECTION("Left intervals")
    {
        const auto tree = IntervalTree(Test::leftIntervals());
        const auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(0 == count);
    }


    SECTION("Left and inner intervals")
    {
        const auto intervals = Test::compositeIntervals(Test::leftIntervals(), Test::innerIntervals());
        const auto tree = IntervalTree(intervals);
        const auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == Test::innerIntervals().size());
    }


    SECTION("Right intervals")
    {
        const auto tree = IntervalTree(Test::rightIntervals());
        const auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(0 == count);
    }


    SECTION("Right and inner intervals")
    {
        const auto intervals = Test::compositeIntervals(Test::rightIntervals(), Test::innerIntervals());
        const auto tree = IntervalTree(intervals);
        const auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == Test::innerIntervals().size());
    }


    SECTION("Left overlapping intervals")
    {
        const auto tree = IntervalTree(Test::leftOverlappingIntervals());
        const auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == Test::leftOverlappingIntervals().size());
    }


    SECTION("Left overlapping and inner intervals")
    {
        const auto intervals = Test::compositeIntervals(Test::leftOverlappingIntervals(), Test::innerIntervals());
        const auto tree = IntervalTree(intervals);
        const auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }


    SECTION("Right overlapping intervals")
    {
        const auto tree = IntervalTree(Test::rightOverlappingIntervals());
        const auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == Test::rightOverlappingIntervals().size());
    }


    SECTION("Right overlapping and inner intervals")
    {
        const auto intervals = Test::compositeIntervals(Test::rightOverlappingIntervals(), Test::innerIntervals());
        const auto tree = IntervalTree(intervals);
        const auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }
}
