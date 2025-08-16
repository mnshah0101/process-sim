#include "MLFQ.hpp"
#include <iostream>

MLFQ::MLFQ(std::vector<Process> processes, int quanta, int promotion_rate)
    : Scheduler(processes),
      queue_limits({{0, 10}, {1, 20}, {2, 30}, {3, 60}, {4, 120}}),
      queues({{}, {}, {}, {}, {}}),
      t(0),
      quanta(quanta),
      promotion_rate(promotion_rate),
      queue_curr({0, 0, 0, 0, 0}) {}

int MLFQ::first_queue() {
    for (int i = 0; i < queues.size(); i++) {
        if (!queues[i].empty()) {
            return i;
        }
    }
    return -1;
}

void MLFQ::run() {
    while (!processes.empty() || first_queue() >= 0) {
        // Add arriving processes to queue 0
        while (!processes.empty() &&
               processes.front().get_arrival_time() <= t) {
            queues[0].push_back({processes.front(), t});
            processes.erase(processes.begin());
        }

        int q = first_queue();
        int curr = queue_curr[q];
        auto& curr_processing = queues[q];

        if (curr >= curr_processing.size()) curr = 0;

        // Run current process for one quantum
        curr_processing[curr].first.run(quanta);
        t += quanta;

        if (curr_processing[curr].first.get_state() == ProcessState::TERMINATED) {
            processed.push_back(curr_processing[curr].first);
            curr_processing.erase(curr_processing.begin() + curr);
            if (curr >= curr_processing.size()) curr = 0;
        } else {
            // Round-robin index
            curr = (curr + 1) % curr_processing.size();
            // Demotion if process exceeds time limit in queue
            if (t - curr_processing[curr].second > queue_limits[q] && q < 4) {
                curr_processing[curr].second = t;
                queues[q + 1].push_back(curr_processing[curr]);
                curr_processing.erase(curr_processing.begin() + curr);
            }
        }

        queue_curr[q] = curr;

        // Promotion step
        if (t % promotion_rate == 0) {
            for (int i = 1; i < queues.size(); i++) {
                if (!queues[i].empty()) {
                    queues[0].push_back(queues[i][0]);
                    queues[i].erase(queues[i].begin());
                    break;
                }
            }
        }
    }
}

void MLFQ::schedule(const Process new_process) {
    processes.push_back(new_process);
}

void MLFQ::print_state() {
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
