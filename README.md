# IntervalTree

[![Linux Build Status](https://travis-ci.org/IvanPinezhaninov/IntervalTree.svg?branch=master)](https://travis-ci.org/IvanPinezhaninov/IntervalTree)
[![Windows Build Status](https://ci.appveyor.com/api/projects/status/github/IvanPinezhaninov/intervaltree?svg=true)](https://ci.appveyor.com/project/IvanPinezhaninov/intervaltree)
[![MIT License](https://img.shields.io/badge/license-mit-blue.svg?style=flat)](http://opensource.org/licenses/MIT)

## Overview

A red-black self-balancing interval tree C++11 header-only implementation

## Usage

```c++
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
```

## Build and test

```bash
git clone https://github.com/IvanPinezhaninov/IntervalTree.git
cd IntervalTree
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=YES
make -j4
cd ./test
./Test --rng-seed time
```

## License
This code is distributed under the [MIT License](LICENSE)

## Author
[Ivan Pinezhaninov](mailto:ivan.pinezhaninov@gmail.com)
