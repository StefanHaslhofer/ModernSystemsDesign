#pragma once

#include <string.h>
#include <string>

class Computer {
    protected:
        std::string name;
        int numOfCores;
        uint32_t diskSize;

    public:
        Computer(std::string name, int numOfCores, int diskSize);
        void printStats();
        void start(int runtime);
        bool execute(); 
};