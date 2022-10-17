#include "computer.hpp"
#include <iostream>

Computer::Computer(std::string name, int numOfCores, int diskSize) {
    this->name = name;
    this->numOfCores = numOfCores;
    this->diskSize = diskSize;
}

void Computer::printStats() {
    std::cout << "------------------\n" 
    << "Name:" << this->name << "\n"
    << "Cores:" << this->numOfCores << "\n"
    << "Disk:" << this->diskSize << "\n"
    << "------------------\n" << std::endl;
}

void Computer::start(int runtime) {
    bool finished = false;
    for (size_t i = runtime; true; i-=numOfCores)
    {
        finished = execute(i);

        if(finished == true) {
            return;
        }
    }
}

bool Computer::execute(int leftover) {
    for (size_t i = 0; i < numOfCores; i++)
    {
        std::cout << "CPU " << i << ": " << "remaining task length: " << (leftover - i) << "\n" << std::endl;

        if (i == leftover) {
            return true;
        }
    }

    return false;
}