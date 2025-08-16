#pragma once

#include <map>
#include <vector>
#include <string>
#include "process.hpp"
#include "scheduler.hpp"

class MLFQ : public Scheduler {
private:
    std::map<int, int> queue_limits;
    std::vector<std::vector<std::pair<Process, int>>> queues;
    int t;
    int quanta;
    int promotion_rate;
    std::vector<int> queue_curr;
    std::vector<Process> processed;

    int first_queue();

public:
    MLFQ(std::vector<Process> processes, int quanta, int promotion_rate);

    void run() override;
    void schedule(const Process new_process) override;
    void print_state() override;
};
