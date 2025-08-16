#include "FCFS.hpp"
#include <algorithm>
#include <iostream>
#include <utility>

FCFS_Scheduler::FCFS_Scheduler(std::vector<Process> processes)
    : Scheduler(std::move(processes)) {}

void FCFS_Scheduler::schedule(const Process new_process) {
    processes.push_back(new_process);
}

void FCFS_Scheduler::run() {
    std::sort(processes.begin(), processes.end()); 

    while (!processes.empty()) {
        Process proc = processes.front();           
        processes.erase(processes.begin());         

        proc.run();
        t += proc.get_duration();

        if (proc.get_state() == ProcessState::TERMINATED) {
            dead_list.push_back(proc);
        } else {
            proc.wait();
            processes.push_back(proc);
        }
    }
}

void FCFS_Scheduler::print_state() {
    std::cout << "Time: " << t << '\n';
    std::cout << "Processes:\n";
    for (const auto& p : processes) {
        std::cout << p.get_pid() << " " << static_cast<std::string>(p) << '\n';
    }
    std::cout << "Finished Processes:\n";
    for (const auto& p : dead_list) {
        std::cout << p.get_pid() << " " << static_cast<std::string>(p) << '\n';
    }
    std::cout << std::endl;
}
