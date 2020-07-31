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

#include <iostream>
#include "intervaltree.hpp"

using namespace Intervals;

int main()
{
    // Create an interval tree
    IntervalTree<int> tree;

    // Insert intervals to the tree
    tree.insert({20, 30});
    tree.insert({40, 60});
    tree.insert({70, 90});
    tree.insert({60, 70});
    tree.insert({40, 90});
    tree.insert({80, 90});

    // Wanted interval and point
    Interval<int> wantedInterval(50, 80);
    auto wantedPoint = 50;

    // Find intervals
    const auto &overlappingIntervals = tree.findOverlappingIntervals(wantedInterval);
    const auto &innerIntervals = tree.findInnerIntervals(wantedInterval);
    const auto &outerIntervals = tree.findOuterIntervals(wantedInterval);
    const auto &intervalsContainPoint = tree.findIntervalsContainPoint(wantedPoint);

    // Print all intervals
    std::cout << "All intervals:" << std::endl;
    for (const auto &interval : tree.intervals()) {
        std::cout << interval << std::endl;
    }
    std::cout << std::endl;

    // Print overlapping intervals
    std::cout << "Overlapping intervals for " << wantedInterval << ":" << std::endl;
    for (const auto &interval : overlappingIntervals) {
        std::cout << interval << std::endl;
    }
    std::cout << std::endl;

    // Print inner intervals
    std::cout << "Inner intervals for " << wantedInterval << ":" << std::endl;
    for (const auto &interval : innerIntervals) {
        std::cout << interval << std::endl;
    }
    std::cout << std::endl;

    // Print outer intervals
    std::cout << "Outer intervals for " << wantedInterval << ":" << std::endl;
    for (const auto &interval : outerIntervals) {
        std::cout << interval << std::endl;
    }
    std::cout << std::endl;

    // Print intervals contain the point
    std::cout << "Intervals contain the point with the value "
              << wantedPoint << ":" << std::endl;
    for (const auto &interval : intervalsContainPoint) {
        std::cout << interval << std::endl;
    }

    return 0;
}
