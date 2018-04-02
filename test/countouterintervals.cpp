#include "catch.hpp"
#include "intervals.h"


TEST_CASE("Count outer intervals")
{
    SECTION("Empty tree")
    {
        const IntervalTree tree;
        const auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(tree.isEmpty());
        REQUIRE(0 == count);
    }


    SECTION("Boundary interval")
    {
        const auto tree = IntervalTree(Test::boundaryIntervals());
        const auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::boundaryIntervals().size());
    }


    SECTION("Outer intervals")
    {
        const auto tree = IntervalTree(Test::outerIntervals());
        const auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::outerIntervals().size());
    }


    SECTION("Outer and boundary intervals")
    {
        const auto intervals = Test::compositeIntervals(Test::outerIntervals(), Test::boundaryIntervals());
        const auto tree = IntervalTree(intervals);
        const auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }


    SECTION("Inner intervals")
    {
        const auto tree = IntervalTree(Test::innerIntervals());
        const auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(0 == count);
    }


    SECTION("Inner and boundary intervals")
    {
        const auto intervals = Test::compositeIntervals(Test::innerIntervals(), Test::boundaryIntervals());
        const auto tree = IntervalTree(intervals);
        const auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::boundaryIntervals().size());
    }


    SECTION("Outer and inner intervals")
    {
        const auto intervals = Test::compositeIntervals(Test::outerIntervals(), Test::innerIntervals());
        const auto tree = IntervalTree(intervals);
        const auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::outerIntervals().size());
    }


    SECTION("Left intervals")
    {
        const auto tree = IntervalTree(Test::leftIntervals());
        const auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(0 == count);
    }


    SECTION("Left and outer intervals")
    {
        const auto intervals = Test::compositeIntervals(Test::leftIntervals(), Test::outerIntervals());
        const auto tree = IntervalTree(intervals);
        const auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::outerIntervals().size());
    }


    SECTION("Right intervals")
    {
        const auto tree = IntervalTree(Test::rightIntervals());
        const auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(0 == count);
    }


    SECTION("Right and outer intervals")
    {
        const auto intervals = Test::compositeIntervals(Test::rightIntervals(), Test::outerIntervals());
        const auto tree = IntervalTree(intervals);
        const auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::outerIntervals().size());
    }


    SECTION("Left overlapping intervals")
    {
        const auto tree = IntervalTree(Test::leftOverlappingIntervals());
        const auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(0 == count);
    }


    SECTION("Left overlapping and outer intervals")
    {
        const auto intervals = Test::compositeIntervals(Test::leftOverlappingIntervals(), Test::outerIntervals());
        const auto tree = IntervalTree(intervals);
        const auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::outerIntervals().size());
    }


    SECTION("Right overlapping intervals")
    {
        const auto tree = IntervalTree(Test::rightOverlappingIntervals());
        const auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(0 == count);
    }


    SECTION("Right overlapping and outer intervals")
    {
        const auto intervals = Test::compositeIntervals(Test::rightOverlappingIntervals(), Test::outerIntervals());
        const auto tree = IntervalTree(intervals);
        const auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::outerIntervals().size());
    }
}
