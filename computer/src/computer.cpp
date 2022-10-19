#include "computer.hpp"
#include <iostream>

int leftover;

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
    leftover = runtime;
    
    while(!execute());
}

bool Computer::execute() {
    for (int i = 0; i < numOfCores; i++)
    {
        std::cout << "CPU " << i << ": " << "remaining task length: " << leftover << std::endl;

        if(leftover == 0) {
            return true;
        }

        leftover--;
    }

    return false;
}