#ifndef TEST_TIMER_H
#define TEST_TIMER_H

#include <chrono>
#include <string>


namespace Timer {

using Time = std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds>;

Time now();

void printTimeElapsed(const Time &start, size_t iterationsCount, const std::string &text);

} // namespace Timer

#endif // TEST_TIMER_H
