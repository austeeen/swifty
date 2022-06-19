#include "benchmark.hpp"

Clock Benchmarker::wall_clock;
Clock Benchmarker::build_clock;
Clock Benchmarker::run_clock;
Clock Benchmarker::frame_clock;

float Benchmarker::wall_time = 0.f;
float Benchmarker::build_time = 0.f;
float Benchmarker::run_time = 0.f;
float Benchmarker::frame_time = 0.f;
int Benchmarker::frames_passed = 0;
std::string Benchmarker::stats_str = "";

Clock::Clock()
{
    clear();
}
void Clock::clear()
{
    reset();
    num_ticks = 0;
    elapsed = std::chrono::duration<double>::zero();
}
void Clock::reset()
{
    ticking = false;
    begin = std::chrono::steady_clock::now();
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration<double>::zero();
}
void Clock::tick()
{
    if (ticking)
        stop();
    else
        start();
}
void Clock::start()
{
    num_ticks += 1;
    begin = std::chrono::steady_clock::now();
    ticking = true;
}
void Clock::stop()
{
    end = std::chrono::steady_clock::now();
    duration = (end - begin);
    ticking = false;
}
void Clock::update()
{
    elapsed += duration;
}
