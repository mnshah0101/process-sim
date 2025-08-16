#include <data_reader.hpp>
#include <process.hpp>
#include <string>
#include <vector>
#include <MLFQ.hpp>


using namespace std;


int main(){

    string filename = "../data/test.csv";
    DataReader data{};
    vector<Process> processes = data.readData(filename);
    for (auto &process : processes){
        process.print();
    }

    MLFQ scheduler{processes, 5, 500};
    scheduler.run();
    scheduler.print_state();






}