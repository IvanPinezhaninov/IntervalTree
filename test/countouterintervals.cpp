#include "catch.hpp"
#include "intervals.h"


TEST_CASE("Count outer intervals")
{
    SECTION("Empty tree")
    {
        IntervalTree tree;
        REQUIRE(tree.isEmpty());

        size_t count = tree.countOuterIntervals(Test::interval());

        REQUIRE(0 == count);
    }

    SECTION("Boundary interval")
    {
        IntervalTree tree;

        for (auto interval : Test::boundaryIntervals()) {
            tree.insert(interval);
        }

        size_t count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::boundaryIntervals().size());
    }

    SECTION("Outer intervals")
    {
        IntervalTree tree;

        for (auto interval : Test::outerIntervals()) {
            tree.insert(interval);
        }

        size_t count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::outerIntervals().size());
    }

    SECTION("Outer and boundary intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::outerIntervals(), Test::boundaryIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }

    SECTION("Inner intervals")
    {
        IntervalTree tree;

        for (auto interval : Test::innerIntervals()) {
            tree.insert(interval);
        }

        size_t count = tree.countOuterIntervals(Test::interval());

        REQUIRE(0 == count);
    }

    SECTION("Inner and boundary intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::innerIntervals(), Test::boundaryIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::boundaryIntervals().size());
    }

    SECTION("Outer and inner intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::outerIntervals(), Test::innerIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::outerIntervals().size());
    }

    SECTION("Left intervals")
    {
        IntervalTree tree;

        for (auto interval : Test::leftIntervals()) {
            tree.insert(interval);
        }

        size_t count = tree.countOuterIntervals(Test::interval());

        REQUIRE(0 == count);
    }

    SECTION("Left and outer intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::leftIntervals(), Test::outerIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::outerIntervals().size());
    }

    SECTION("Right intervals")
    {
        IntervalTree tree;

        for (auto interval : Test::rightIntervals()) {
            tree.insert(interval);
        }

        size_t count = tree.countOuterIntervals(Test::interval());

        REQUIRE(0 == count);
    }

    SECTION("Right and outer intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::rightIntervals(), Test::outerIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::outerIntervals().size());
    }

    SECTION("Left overlapping intervals")
    {
        IntervalTree tree;

        for (auto interval : Test::leftOverlappingIntervals()) {
            tree.insert(interval);
        }

        size_t count = tree.countOuterIntervals(Test::interval());

        REQUIRE(0 == count);
    }

    SECTION("Left overlapping and outer intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::leftOverlappingIntervals(), Test::outerIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::outerIntervals().size());
    }

    SECTION("Right overlapping intervals")
    {
        IntervalTree tree;

        for (auto interval : Test::rightOverlappingIntervals()) {
            tree.insert(interval);
        }

        size_t count = tree.countOuterIntervals(Test::interval());

        REQUIRE(0 == count);
    }

    SECTION("Right overlapping and outer intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::rightOverlappingIntervals(), Test::outerIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::outerIntervals().size());
    }
}
