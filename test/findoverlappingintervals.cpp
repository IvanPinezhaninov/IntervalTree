#include "catch.hpp"
#include "intervals.h"


TEST_CASE("Find overlapping intervals")
{
    SECTION("Empty tree")
    {
        IntervalTree tree;
        REQUIRE(tree.isEmpty());

        auto result = tree.findOverlappingIntervals(Test::interval());

        REQUIRE(result.empty());
    }

    SECTION("Boundary interval")
    {
        IntervalTree tree;

        auto intervals = Test::boundaryIntervals();

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        auto result = tree.findOverlappingIntervals(Test::interval());

        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), intervals.cbegin()));
    }

    SECTION("Outer intervals")
    {
        IntervalTree tree;

        auto intervals = Test::outerIntervals();

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        auto result = tree.findOverlappingIntervals(Test::interval());

        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), intervals.cbegin()));
    }

    SECTION("Outer and boundary intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::outerIntervals(), Test::boundaryIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        auto result = tree.findOverlappingIntervals(Test::interval());

        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), intervals.cbegin()));
    }

    SECTION("Inner intervals")
    {
        IntervalTree tree;

        auto intervals = Test::innerIntervals();

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        auto result = tree.findOverlappingIntervals(Test::interval());

        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), intervals.cbegin()));
    }

    SECTION("Inner and boundary intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::innerIntervals(), Test::boundaryIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        auto result = tree.findOverlappingIntervals(Test::interval());

        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), intervals.cbegin()));
    }

    SECTION("Outer and inner intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::outerIntervals(), Test::innerIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        auto result = tree.findOverlappingIntervals(Test::interval());

        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), intervals.cbegin()));
    }

    SECTION("Left intervals")
    {
        IntervalTree tree;

        auto intervals = Test::leftIntervals();

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        auto result = tree.findOverlappingIntervals(Test::interval());

        REQUIRE(result.empty());
    }

    SECTION("Left and inner intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::leftIntervals(), Test::innerIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        auto result = tree.findOverlappingIntervals(Test::interval());

        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), Test::innerIntervals().cbegin()));
    }

    SECTION("Right intervals")
    {
        IntervalTree tree;

        auto intervals = Test::rightIntervals();

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        auto result = tree.findOverlappingIntervals(Test::interval());

        REQUIRE(result.empty());
    }

    SECTION("Right and inner intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::rightIntervals(), Test::innerIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        auto result = tree.findOverlappingIntervals(Test::interval());

        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), Test::innerIntervals().cbegin()));
    }

    SECTION("Left overlapping intervals")
    {
        IntervalTree tree;

        auto intervals = Test::leftOverlappingIntervals();

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        auto result = tree.findOverlappingIntervals(Test::interval());

        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), intervals.cbegin()));
    }

    SECTION("Left overlapping and inner intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::leftOverlappingIntervals(), Test::innerIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        auto result = tree.findOverlappingIntervals(Test::interval());

        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), intervals.cbegin()));
    }

    SECTION("Right overlapping intervals")
    {
        IntervalTree tree;

        auto intervals = Test::rightOverlappingIntervals();

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        auto result = tree.findOverlappingIntervals(Test::interval());

        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), intervals.cbegin()));
    }

    SECTION("Right overlapping and inner intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::rightOverlappingIntervals(), Test::innerIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        auto result = tree.findOverlappingIntervals(Test::interval());

        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), intervals.cbegin()));
    }
}
