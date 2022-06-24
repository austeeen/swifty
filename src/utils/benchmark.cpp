#include "benchmark.hpp"


Clock::Clock()
{
    restart();
}
void Clock::restart()
{
    num_ticks = 0;
    begin = std::chrono::steady_clock::now();
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration<double>::zero();
}
void Clock::tick()
{
    num_ticks += 1;
}
void Clock::start()
{
    begin = std::chrono::steady_clock::now();
}
void Clock::stop()
{
    end = std::chrono::steady_clock::now();
    duration = (end - begin);
}
