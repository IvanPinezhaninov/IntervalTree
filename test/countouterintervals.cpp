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


TEST_CASE("Count outer intervals")
{
    SECTION("Empty tree")
    {
        IntervalTree tree;
        auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(tree.isEmpty());
        REQUIRE(0 == count);
    }


    SECTION("Boundary interval")
    {
        IntervalTree tree(Test::boundaryIntervals());

        auto count = tree.countOuterIntervals(Test::interval(), true);
        REQUIRE(count == Test::boundaryIntervals().size());

        count = tree.countOuterIntervals(Test::interval(), false);
        REQUIRE(0 == count);
    }


    SECTION("Outer intervals")
    {
        IntervalTree tree(Test::outerIntervals());
        auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::outerIntervals().size());
    }


    SECTION("Outer and boundary intervals")
    {
        const auto &intervals = Test::compositeIntervals(Test::outerIntervals(), Test::boundaryIntervals());
        IntervalTree tree(intervals);
        auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == intervals.size());
    }


    SECTION("Inner intervals")
    {
        IntervalTree tree(Test::innerIntervals());
        auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(0 == count);
    }


    SECTION("Inner and boundary intervals")
    {
        const auto &intervals = Test::compositeIntervals(Test::innerIntervals(), Test::boundaryIntervals());
        IntervalTree tree(intervals);
        auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::boundaryIntervals().size());
    }


    SECTION("Outer and inner intervals")
    {
        const auto &intervals = Test::compositeIntervals(Test::outerIntervals(), Test::innerIntervals());
        IntervalTree tree(intervals);
        auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::outerIntervals().size());
    }


    SECTION("Left intervals")
    {
        IntervalTree tree(Test::leftIntervals());
        auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(0 == count);
    }


    SECTION("Left and outer intervals")
    {
        const auto &intervals = Test::compositeIntervals(Test::leftIntervals(), Test::outerIntervals());
        IntervalTree tree(intervals);
        auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::outerIntervals().size());
    }


    SECTION("Right intervals")
    {
        IntervalTree tree(Test::rightIntervals());
        auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(0 == count);
    }


    SECTION("Right and outer intervals")
    {
        const auto &intervals = Test::compositeIntervals(Test::rightIntervals(), Test::outerIntervals());
        IntervalTree tree(intervals);
        auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::outerIntervals().size());
    }


    SECTION("Left overlapping intervals")
    {
        IntervalTree tree(Test::leftOverlappingIntervals());
        auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(0 == count);
    }


    SECTION("Left overlapping and outer intervals")
    {
        const auto &intervals = Test::compositeIntervals(Test::leftOverlappingIntervals(), Test::outerIntervals());
        IntervalTree tree(intervals);
        auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::outerIntervals().size());
    }


    SECTION("Right overlapping intervals")
    {
        IntervalTree tree(Test::rightOverlappingIntervals());
        auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(0 == count);
    }


    SECTION("Right overlapping and outer intervals")
    {
        const auto &intervals = Test::compositeIntervals(Test::rightOverlappingIntervals(), Test::outerIntervals());
        IntervalTree tree(intervals);
        auto count = tree.countOuterIntervals(Test::interval());

        REQUIRE(count == Test::outerIntervals().size());
    }
}
