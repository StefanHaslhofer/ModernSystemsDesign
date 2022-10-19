#include "cloud.hpp"
#include "cloudServer.hpp"
#include <iostream>
#include <vector>

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