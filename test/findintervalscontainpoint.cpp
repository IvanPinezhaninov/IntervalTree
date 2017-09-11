#include "catch.hpp"
#include "intervals.h"

static const int centralPoint = 450;
static const int leftBoundaryPoint = 400;
static const int rightBoundaryPoint = 500;

TEST_CASE("Find intervals contain point")
{
    SECTION("Empty tree")
    {
        IntervalTree tree;
        REQUIRE(tree.isEmpty());

        auto result = tree.findIntervalsContainPoint(centralPoint);

        REQUIRE(result.empty());
    }

    SECTION("Boundary interval central point")
    {
        IntervalTree tree;

        for (auto interval : Test::boundaryIntervals()) {
            tree.insert(interval);
        }

        auto result = tree.findIntervalsContainPoint(centralPoint);

        REQUIRE_FALSE(result.empty());
        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), Test::boundaryIntervals().cbegin()));
    }

    SECTION("Boundary interval left boundary point")
    {
        IntervalTree tree;

        for (auto interval : Test::boundaryIntervals()) {
            tree.insert(interval);
        }

        auto result = tree.findIntervalsContainPoint(leftBoundaryPoint);

        REQUIRE_FALSE(result.empty());
        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), Test::boundaryIntervals().cbegin()));
    }

    SECTION("Boundary interval right boundary point")
    {
        IntervalTree tree;

        for (auto interval : Test::boundaryIntervals()) {
            tree.insert(interval);
        }

        auto result = tree.findIntervalsContainPoint(rightBoundaryPoint);

        REQUIRE_FALSE(result.empty());
        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), Test::boundaryIntervals().cbegin()));
    }

    SECTION("Outer and boundary intervals central point")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::outerIntervals(), Test::boundaryIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        auto result = tree.findIntervalsContainPoint(centralPoint);

        REQUIRE_FALSE(result.empty());
        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), intervals.cbegin()));
    }

    SECTION("Outer and boundary intervals left boundary point")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::outerIntervals(), Test::boundaryIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        auto result = tree.findIntervalsContainPoint(leftBoundaryPoint);

        REQUIRE_FALSE(result.empty());
        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), intervals.cbegin()));
    }

    SECTION("Outer and boundary intervals right boundary point")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::outerIntervals(), Test::boundaryIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        auto result = tree.findIntervalsContainPoint(rightBoundaryPoint);

        REQUIRE_FALSE(result.empty());
        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), intervals.cbegin()));
    }

    SECTION("Left intervals")
    {
        IntervalTree tree;

        for (auto interval : Test::leftIntervals()) {
            tree.insert(interval);
        }

        auto result = tree.findIntervalsContainPoint(centralPoint);

        REQUIRE(result.empty());
    }

    SECTION("Left and inner intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::leftIntervals(), Test::innerIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        auto result = tree.findIntervalsContainPoint(centralPoint);

        REQUIRE_FALSE(result.empty());
        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), Test::innerIntervals().cbegin()));
    }

    SECTION("Right intervals")
    {
        IntervalTree tree;

        for (auto interval : Test::rightIntervals()) {
            tree.insert(interval);
        }

        auto result = tree.findIntervalsContainPoint(centralPoint);

        REQUIRE(result.empty());
    }

    SECTION("Right and inner intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::rightIntervals(), Test::innerIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        auto result = tree.findIntervalsContainPoint(centralPoint);

        REQUIRE_FALSE(result.empty());
        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), Test::innerIntervals().cbegin()));
    }

    SECTION("Left overlapping intervals and left boundary point")
    {
        IntervalTree tree;

        for (auto interval : Test::leftOverlappingIntervals()) {
            tree.insert(interval);
        }

        auto result = tree.findIntervalsContainPoint(leftBoundaryPoint);

        REQUIRE_FALSE(result.empty());
        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), Test::leftOverlappingIntervals().cbegin()));
    }

    SECTION("Right overlapping intervals and right boundary point")
    {
        IntervalTree tree;

        for (auto interval : Test::rightOverlappingIntervals()) {
            tree.insert(interval);
        }

        auto result = tree.findIntervalsContainPoint(rightBoundaryPoint);

        REQUIRE_FALSE(result.empty());
        REQUIRE(std::is_permutation(result.cbegin(), result.cend(), Test::rightOverlappingIntervals().cbegin()));
    }
}
