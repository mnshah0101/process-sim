#include "RoundRobin.hpp"

#include <algorithm>
#include <iostream>
#include <utility>

RoundRobin::RoundRobin(std::vector<Process> p, int q)
    : Scheduler(std::move(p)), quanta(q) {
    // Sort base 'processes' by arrival (assumes operator< sorts appropriately).
    std::sort(processes.begin(), processes.end());
}

void RoundRobin::schedule(const Process new_process) {
    processes.push_back(new_process);
    std::sort(processes.begin(), processes.end());
}

void RoundRobin::run() {
    while (!processes.empty() || !curr_processing.empty()) {
        // Move any newly arrived processes into the ready queue.
        while (!processes.empty() &&
               processes.front().get_arrival_time() <= t) {
            curr_processing.push_back(processes.front());
            processes.erase(processes.begin());
        }

        if (curr_processing.empty()) {
            // Nothing ready: jump time to next arrival to avoid stalling.
            if (!processes.empty()) {
                t = std::max(t, processes.front().get_arrival_time());
                continue;
            } else {
                break;
            }
        }

        if (curr >= curr_processing.size()) curr = 0;

        // Run current process for one quantum.
        curr_processing[curr].run(quanta);
        t += quanta;

        if (curr_processing[curr].get_state() == ProcessState::TERMINATED) {
            processed.push_back(curr_processing[curr]);
            curr_processing.erase(curr_processing.begin() + curr);
            if (curr >= curr_processing.size()) curr = 0;
        } else {
            // Advance round-robin index safely.
            curr = (curr + 1) % curr_processing.size();
        }

        
    }
}

void RoundRobin::print_state()  {
    std::cout << "Time: " << t << '\n';
    std::cout << "Processes:\n";
    for (const auto& p : processes) {
        std::cout << p.get_pid() << " " << static_cast<std::string>(p) << '\n';
    }
    std::cout << "Finished Processes:\n";
    for (const auto& p : processed) {
        std::cout << p.get_pid() << " " << static_cast<std::string>(p) << '\n';
    }
    std::cout << std::endl;
}
