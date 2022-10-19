#pragma once
#include <vector>
#include "cloudServer.hpp"

class Cloud {
    public:
        std::vector<CloudServer*> servers;

    public:
        Cloud();
        unsigned int add(std::string ip, std::string name, int numOfCores, int diskSize);
        bool remove(unsigned int serverId);
        void start(int runtime);
        void run();
};