#pragma once
#include <string>
#include <vector>
#include "process.hpp"   // depends on Process

class DataReader {
public:
    DataReader() = default;
    ~DataReader() = default;

    // reads CSV file, returns vector of Process objects
    std::vector<Process> readData(const std::string& file_name);

private:
    int size {};   // initialize to 0
};
