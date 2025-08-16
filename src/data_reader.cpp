#include "data_reader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Process> DataReader::readData(const std::string& file_name) {
    std::ifstream fin(file_name);
    std::vector<Process> ret_arr;

    std::string line;
    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        std::vector<std::string> cols;
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            cols.push_back(cell);
        }

        if (cols.size() != 3) {
            std::cerr << "Error in file format\n";
            std::exit(1);
        }

        Process p(std::stoi(cols[0]), std::stoi(cols[1]), std::stoi(cols[2]));
        ret_arr.push_back(std::move(p));
    }
    return ret_arr;
}
