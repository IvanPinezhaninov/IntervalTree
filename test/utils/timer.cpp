#include "timer.h"

#include <iomanip>
#include <iostream>


Timer::Time Timer::now()
{
    return std::chrono::steady_clock::now();
}


void Timer::printTimeElapsed(const Timer::Time &start, size_t iterationsCount, const std::string &text)
{
    using Ns = std::chrono::nanoseconds;
    const Time &end = std::chrono::steady_clock::now();
    const double totalDuration = std::chrono::duration_cast<Ns>(end - start).count() * 0.000001;
    const double iterationDuration = totalDuration / iterationsCount;
    std::cout << "[" <<std::fixed << std::setw(7)
              << std::setprecision(3) << std::setfill(' ') << totalDuration << " ("
              << std::setprecision(4) << iterationDuration << ") ms]: " << text << std::endl;
}
