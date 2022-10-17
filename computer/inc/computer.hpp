#pragma once

#include <string.h>

class Computer {
    private:
        std::string name;
        int numOfCores;
        int diskSize;

    public:
        Computer(std::string name, int numOfCores, int diskSize);
        void printStats();
        void start(int runtime);
        bool execute(); 
};