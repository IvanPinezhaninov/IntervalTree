/******************************************************************************
**
** Copyright (C) 2020 Ivan Pinezhaninov <ivan.pinezhaninov@gmail.com>
**
** This file is part of the IntervalTree - Red-Black balanced interval tree
** which can be found at https://github.com/IvanPinezhaninov/IntervalTree/.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
** OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
** THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
******************************************************************************/

#include "catch.hpp"
#include "intervals.h"


TEST_CASE("Count overlapping intervals")
{
    SECTION("Empty tree")
    {
        IntervalTree tree;
        auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(tree.isEmpty());
        REQUIRE(0 == count);
    }


    SECTION("Boundary interval")
    {
        IntervalTree tree(Test::boundaryIntervals());
        auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == Test::boundaryIntervals().size());
    }


    SECTION("Left boundary intervals")
    {
        IntervalTree tree(Test::leftBoundaryIntervals());

        auto count = tree.countOverlappingIntervals(Test::interval(), true);
        REQUIRE(count == Test::leftBoundaryIntervals().size());

        count = tree.countOverlappingIntervals(Test::interval(), false);
        REQUIRE(0 == count);
    }


    SECTION("Right boundary intervals")
    {
        IntervalTree tree(Test::rightBoundaryIntervals());

        auto count = tree.countOverlappingIntervals(Test::interval(), true);
        REQUIRE(count == Test::rightBoundaryIntervals().size());

        count = tree.countOverlappingIntervals(Test::interval(), false);
        REQUIRE(0 == count);
    }


    SECTION("Outer intervals")
    {
        const auto &intervals = Test::outerIntervals();
        IntervalTree tree(intervals);
        auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }


    SECTION("Outer and boundary intervals")
    {
        const auto &intervals = Test::compositeIntervals(Test::outerIntervals(), Test::boundaryIntervals());
        IntervalTree tree(intervals);
        auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }


    SECTION("Inner intervals")
    {
        IntervalTree tree(Test::innerIntervals());
        auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == Test::innerIntervals().size());
    }


    SECTION("Inner and boundary intervals")
    {
        const auto &intervals = Test::compositeIntervals(Test::innerIntervals(), Test::boundaryIntervals());
        IntervalTree tree(intervals);
        auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }


    SECTION("Outer and inner intervals")
    {
        const auto &intervals = Test::compositeIntervals(Test::outerIntervals(), Test::innerIntervals());
        IntervalTree tree(intervals);
        auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }


    SECTION("Left intervals")
    {
        IntervalTree tree(Test::leftIntervals());
        auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(0 == count);
    }


    SECTION("Left and inner intervals")
    {
        const auto &intervals = Test::compositeIntervals(Test::leftIntervals(), Test::innerIntervals());
        IntervalTree tree(intervals);
        auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == Test::innerIntervals().size());
    }


    SECTION("Right intervals")
    {
        IntervalTree tree(Test::rightIntervals());
        auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(0 == count);
    }


    SECTION("Right and inner intervals")
    {
        const auto &intervals = Test::compositeIntervals(Test::rightIntervals(), Test::innerIntervals());
        IntervalTree tree(intervals);
        auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == Test::innerIntervals().size());
    }


    SECTION("Left overlapping intervals")
    {
        IntervalTree tree(Test::leftOverlappingIntervals());
        auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == Test::leftOverlappingIntervals().size());
    }


    SECTION("Left overlapping and inner intervals")
    {
        const auto &intervals = Test::compositeIntervals(Test::leftOverlappingIntervals(), Test::innerIntervals());
        IntervalTree tree(intervals);
        auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }


    SECTION("Right overlapping intervals")
    {
        IntervalTree tree(Test::rightOverlappingIntervals());
        auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == Test::rightOverlappingIntervals().size());
    }


    SECTION("Right overlapping and inner intervals")
    {
        const auto &intervals = Test::compositeIntervals(Test::rightOverlappingIntervals(), Test::innerIntervals());
        IntervalTree tree(intervals);
        auto count = tree.countOverlappingIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }
}
