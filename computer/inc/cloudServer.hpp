#pragma once
#include "computer.hpp"
#include <string.h>
#include <string>

class CloudServer: public Computer {
    private:
        std::string ip;
        uint32_t storedData;

    public:
        CloudServer(std::string ip, std::string name, int numOfCores, int diskSize);
        bool store(uint32_t size);
        void free(uint32_t size);
        void printStats();
};