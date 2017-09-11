#include "catch.hpp"
#include "intervals.h"

static const int centralPoint = 450;
static const int leftBoundaryPoint = 400;
static const int rightBoundaryPoint = 500;

TEST_CASE("Count intervals contain point")
{
    SECTION("Empty tree")
    {
        IntervalTree tree;
        REQUIRE(tree.isEmpty());

        size_t count = tree.countIntervalsContainPoint(centralPoint);

        REQUIRE(0 == count);
    }

    SECTION("Boundary interval central point")
    {
        IntervalTree tree;

        for (auto interval : Test::boundaryIntervals()) {
            tree.insert(interval);
        }

        size_t count = tree.countIntervalsContainPoint(centralPoint);

        REQUIRE(count == Test::boundaryIntervals().size());
    }

    SECTION("Boundary interval left boundary point")
    {
        IntervalTree tree;

        for (auto interval : Test::boundaryIntervals()) {
            tree.insert(interval);
        }

        size_t count = tree.countIntervalsContainPoint(leftBoundaryPoint);

        REQUIRE(count == Test::boundaryIntervals().size());
    }

    SECTION("Boundary interval right boundary point")
    {
        IntervalTree tree;

        for (auto interval : Test::boundaryIntervals()) {
            tree.insert(interval);
        }

        size_t count = tree.countIntervalsContainPoint(rightBoundaryPoint);

        REQUIRE(count == Test::boundaryIntervals().size());
    }

    SECTION("Outer and boundary intervals central point")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::outerIntervals(), Test::boundaryIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countIntervalsContainPoint(centralPoint);

        REQUIRE(count == intervals.size());
    }

    SECTION("Outer and boundary intervals left boundary point")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::outerIntervals(), Test::boundaryIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countIntervalsContainPoint(leftBoundaryPoint);

        REQUIRE(count == intervals.size());
    }

    SECTION("Outer and boundary intervals right boundary point")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::outerIntervals(), Test::boundaryIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countIntervalsContainPoint(rightBoundaryPoint);

        REQUIRE(count == intervals.size());
    }

    SECTION("Left intervals")
    {
        IntervalTree tree;

        for (auto interval : Test::leftIntervals()) {
            tree.insert(interval);
        }

        size_t count = tree.countIntervalsContainPoint(centralPoint);

        REQUIRE(0 == count);
    }

    SECTION("Left and inner intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::leftIntervals(), Test::innerIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countIntervalsContainPoint(centralPoint);

        REQUIRE(count == Test::innerIntervals().size());
    }

    SECTION("Right intervals")
    {
        IntervalTree tree;

        for (auto interval : Test::rightIntervals()) {
            tree.insert(interval);
        }

        size_t count = tree.countIntervalsContainPoint(centralPoint);

        REQUIRE(0 == count);
    }

    SECTION("Right and inner intervals")
    {
        IntervalTree tree;

        auto intervals = Test::compositeIntervals(Test::rightIntervals(), Test::innerIntervals());

        for (auto interval : intervals) {
            tree.insert(interval);
        }

        size_t count = tree.countIntervalsContainPoint(centralPoint);

        REQUIRE(count == Test::innerIntervals().size());
    }

    SECTION("Left overlapping intervals and left boundary point")
    {
        IntervalTree tree;

        for (auto interval : Test::leftOverlappingIntervals()) {
            tree.insert(interval);
        }

        size_t count = tree.countIntervalsContainPoint(leftBoundaryPoint);

        REQUIRE(count == Test::leftOverlappingIntervals().size());
    }

    SECTION("Right overlapping intervals and right boundary point")
    {
        IntervalTree tree;

        for (auto interval : Test::rightOverlappingIntervals()) {
            tree.insert(interval);
        }

        size_t count = tree.countIntervalsContainPoint(rightBoundaryPoint);

        REQUIRE(count == Test::rightOverlappingIntervals().size());
    }
}
