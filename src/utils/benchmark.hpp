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
    void clear();
    void reset();
    void tick();
    void start();
    void stop();
    void update();

    double getElapsed() { return elapsed.count(); };
    double getAvg() { return elapsed.count() / num_ticks; };

    bool ticking;
    int num_ticks;
    time_val begin;
    time_val end;
    dur duration;
    dur elapsed;
};

class Benchmarker
{
public:
    static void start() {
        wall_clock.reset();
        wall_clock.start();
    }
    static void startBuild() {
        build_clock.reset();
        build_clock.start();
    }
    static void startRunning() {
        run_clock.reset();
        run_clock.start();
    }
    static void stop() {
        wall_clock.stop();
        wall_clock.update();
    }
    static void stopBuild() {
        build_clock.stop();
        build_clock.update();
    }
    static void stopRunning() {
        run_clock.stop();
        run_clock.update();
    }

    static void updateFrame() {
        frame_clock.update();
    }

    static void recordTimes() {
        wall_time = wall_clock.getElapsed();
        build_time = build_clock.getElapsed();
        run_time = run_clock.getElapsed();
        frame_time = frame_clock.getElapsed();
        // todo frames_passed = frame_clock.get_avg();
    }
    static void report() {
        recordTimes();
        std::cout << "wall time: " << wall_time << ",\n";
        std::cout << "build time: " << build_time << ",\n";
        std::cout << "run time: " << run_time << ",\n";
        std::cout << "frame time: " << frame_time << ",\n";
        std::cout << "num frames: " << frame_clock.num_ticks << ",\n";
        std::cout << "avg frame time: " << frame_clock.getAvg() << "\n";
    }

    static Clock wall_clock, build_clock, run_clock, frame_clock;
    static float wall_time, build_time, run_time, frame_time;
    static int frames_passed;
    static std::string stats_str;
};

#endif // UTL_BENCHMARK_H
