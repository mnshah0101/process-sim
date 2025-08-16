#pragma once

#include <scheduler.hpp>
#include <process.hpp>
#include <vector>
#include <iostream>
#include <algorithm>

class FCFS_Scheduler : public Scheduler {
private:
    std::vector<Process> dead_list;
    int t{};

public:
    explicit FCFS_Scheduler(std::vector<Process> processes);

    void schedule(Process new_process);
    void run();
    void print_state();
};
