#ifndef UTL_BENCHMARK_H
#define UTL_BENCHMARK_H

#include <iostream>
#include <chrono>


typedef std::chrono::time_point<std::chrono::steady_clock> time_val;
typedef std::chrono::duration<double> dur;

class Clock
{
public:
    Clock();
    void restart();
    void tick();
    void start();
    void stop();

    int num_ticks;
    time_val begin;
    time_val end;
    dur duration;
};

#endif // UTL_BENCHMARK_H
