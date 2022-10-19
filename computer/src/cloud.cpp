#include "cloud.hpp"
#include "cloudServer.hpp"
#include <iostream>
#include <vector>

int processRuntime;

Cloud::Cloud() {
}

unsigned int Cloud::add(std::string ip, std::string name, int numOfCores, int diskSize) {
    this->servers.push_back(new CloudServer(ip, name, numOfCores, diskSize));

    return this->servers.size()-1;
}

bool Cloud::remove(unsigned int serverId) {
    CloudServer *pt = servers[serverId];
    servers.erase(servers.begin() + serverId);
    delete pt;

    return true;
}

void Cloud::start(int runtime) {
    processRuntime = runtime;
    
    run();
}

void Cloud::run() {
    for (int i = 0; i < servers.size(); i++)
    {
        servers[i]->start(processRuntime);
    }
}