#include "catch.hpp"
#include "intervals.h"


TEST_CASE("Count overlapping intervals")
{
    SECTION("Empty tree")
    {
        IntervalTree tree;
        REQUIRE(tree.isEmpty());

        size_t count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(0 == count);
    }

    SECTION("Boundary interval")
    {
        IntervalTree tree;

        auto intervals = Test::boundaryIntervals();

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }

    SECTION("Outer intervals")
    {
        IntervalTree tree;

        auto intervals = Test::outerIntervals();

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }

    SECTION("Outer and boundary intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::outerIntervals(), Test::boundaryIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }

    SECTION("Inner intervals")
    {
        IntervalTree tree;

        auto intervals = Test::innerIntervals();

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }

    SECTION("Inner and boundary intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::innerIntervals(), Test::boundaryIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }

    SECTION("Outer and inner intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::outerIntervals(), Test::innerIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }

    SECTION("Left intervals")
    {
        IntervalTree tree;

        auto intervals = Test::leftIntervals();

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(0 == count);
    }

    SECTION("Left and inner intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::leftIntervals(), Test::innerIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == Test::innerIntervals().size());
    }

    SECTION("Right intervals")
    {
        IntervalTree tree;

        auto intervals = Test::rightIntervals();

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(0 == count);
    }

    SECTION("Right and inner intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::rightIntervals(), Test::innerIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == Test::innerIntervals().size());
    }

    SECTION("Left overlapping intervals")
    {
        IntervalTree tree;

        auto intervals = Test::leftOverlappingIntervals();

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }

    SECTION("Left overlapping and inner intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::leftOverlappingIntervals(), Test::innerIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }

    SECTION("Right overlapping intervals")
    {
        IntervalTree tree;

        auto intervals = Test::rightOverlappingIntervals();

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }

    SECTION("Right overlapping and inner intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::rightOverlappingIntervals(), Test::innerIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }
}
