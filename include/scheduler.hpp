#pragma once
#include <string>
#include <process.hpp>
#include <vector>






class Scheduler{

    protected:
        std::vector<Process> processes;

    public:
        Scheduler(std::vector<Process> _processes){
            processes = _processes;
        }
        virtual void schedule(Process new_process) = 0;
        virtual void print_state() = 0;
        virtual void run() = 0;



};