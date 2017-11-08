#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include "common.h"
#include "random.h"


TEST_CASE("Intervals with the same boundaries and different values")
{
    IntervalVector intervals
    {
        { 1, 2, 1 },
        { 1, 2, 2 }
    };

    IntervalTree intervalTree;

    for (auto interval : intervals) {
        REQUIRE(intervalTree.insert(interval));
    }

    for (auto interval : intervals) {
        REQUIRE_FALSE(intervalTree.insert(interval));
    }

    auto treeIntervals = intervalTree.intervals();

    REQUIRE_FALSE(treeIntervals.empty());
    REQUIRE(std::is_permutation(treeIntervals.cbegin(), treeIntervals.cend(), intervals.cbegin()));
}


int main(int argc, char* argv[]) {
    Catch::Session session;

    const auto res = session.applyCommandLine(argc, argv);
    if (0 != res) {
        return res;
    }

    const auto seed = session.config().rngSeed();
    if (0 != seed) {
        Random::setRndGeneratorSeed(seed);
    }

    return session.run(argc, argv);
}
