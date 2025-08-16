#pragma once
#include <iostream>
#include <string>

// Scoped enum is preferred to avoid polluting global namespace
enum class ProcessState {
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};

class Process {
private:
    int pid;
    int priority;
    int arrival_time;
    int duration;
    ProcessState state;

public:
    Process(int pid, int arrival_time, int duration);

    int get_pid() const;
    int get_priority() const;
    int get_arrival_time() const;
    int get_duration() const;
    ProcessState get_state() const;

    void set_pid(int pid);
    void set_priority(int priority);
    void set_arrival_time(int arrival_time);
    void set_duration(int duration);
    void set_state(ProcessState state);
    void wait(){
        ;
    }
    void run(){
        state = ProcessState::TERMINATED;
    }

    void run(int time) {
        duration -= time;
        if (duration <= 0) {
            state = ProcessState::TERMINATED;
        }
    };

    void print() const;
     explicit operator std::string() const {
            return "Process: " + std::to_string(pid);
        }

        bool operator < (const Process& other) const
    {
        return (arrival_time < other.arrival_time);
    }

};
