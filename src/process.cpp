#include "process.hpp"

Process::Process(int pid, int arrival_time, int duration)
    : pid(pid),
      priority(0),  // default
      arrival_time(arrival_time),
      duration(duration),
      state(ProcessState::READY) {}

int Process::get_pid() const { return pid; }
int Process::get_priority() const { return priority; }
int Process::get_arrival_time() const { return arrival_time; }
int Process::get_duration() const { return duration; }
ProcessState Process::get_state() const { return state; }

void Process::set_pid(int _pid) { pid = _pid; }
void Process::set_priority(int _priority) { priority = _priority; }
void Process::set_arrival_time(int _arrival_time) { arrival_time = _arrival_time; }
void Process::set_duration(int _duration) { duration = _duration; }
void Process::set_state(ProcessState _state) { state = _state; }

void Process::print() const {
    std::cout << "PID: " << pid
              << " Priority: " << priority
              << " Arrival Time: " << arrival_time
              << " Duration: " << duration
              << " State: " << static_cast<int>(state)
              << std::endl;
}
