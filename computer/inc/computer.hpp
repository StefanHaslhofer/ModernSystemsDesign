#pragma once

#include <string.h>
#include <string>

class Computer {
    private:
        std::string name;
        int numOfCores;
        int diskSize;

    public:
        Computer(std::string name, int numOfCores, int diskSize);
        void printStats();
        void start(int runtime);
        bool execute(int leftover); 
};