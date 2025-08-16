#pragma once

#include <vector>
#include "scheduler.hpp"
#include "process.hpp"

class RoundRobin : public Scheduler {
public:
    RoundRobin(std::vector<Process> p, int q);

    // If Scheduler declares these virtual, 'override' is correct; otherwise you can drop it.
    void schedule(const Process new_process) override;
    void run() override;
    void print_state();

private:
    int quanta;
    int t{0};
    std::size_t curr{0};
    std::vector<Process> curr_processing;
    std::vector<Process> processed;
};
