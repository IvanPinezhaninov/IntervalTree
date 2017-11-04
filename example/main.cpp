#include <iostream>

#include "intervaltree.hpp"


int main()
{
    // Create an interval tree
    Intervals::IntervalTree<int> intervalTree;

    // Insert intervals to the tree
    intervalTree.insert({ 20, 30 });
    intervalTree.insert({ 40, 60 });
    intervalTree.insert({ 70, 90 });
    intervalTree.insert({ 60, 70 });
    intervalTree.insert({ 40, 90 });
    intervalTree.insert({ 80, 90 });

    // Find intervals
    auto overlappingIntervals = intervalTree.findOverlappingIntervals({ 50, 80 });
    auto innerIntervals = intervalTree.findInnerIntervals({ 50, 80 });
    auto outerIntervals = intervalTree.findOuterIntervals({ 50, 80 });
    auto intervalsContainPoint = intervalTree.findIntervalsContainPoint(50);

    // Print all intervals
    std::cout << "All intervals:" << std::endl;
    for (auto interval : intervalTree.intervals()) {
        std::cout << interval << std::endl;
    }
    std::cout << std::endl;

    // Print overlapping intervals
    std::cout << "Overlapping intervals:" << std::endl;
    for (auto interval : overlappingIntervals) {
        std::cout << interval << std::endl;
    }
    std::cout << std::endl;

    // Print inner intervals
    std::cout << "Inner intervals:" << std::endl;
    for (auto interval : innerIntervals) {
        std::cout << interval << std::endl;
    }
    std::cout << std::endl;

    // Print outer intervals
    std::cout << "Outer intervals:" << std::endl;
    for (auto interval : outerIntervals) {
        std::cout << interval << std::endl;
    }
    std::cout << std::endl;

    // Print intervals contain the point
    std::cout << "Intervals contain the point:" << std::endl;
    for (auto interval : intervalsContainPoint) {
        std::cout << interval << std::endl;
    }

    return 0;
}
