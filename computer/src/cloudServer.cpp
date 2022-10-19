#include "cloudServer.hpp"
#include <iostream>
#include <algorithm>

CloudServer::CloudServer(std::string ip, std::string name, int numOfCores, int diskSize) : Computer(name, numOfCores, diskSize) {
    this->ip = ip;
    this->storedData = 0;
}

bool CloudServer::store(uint32_t size) {
    if(storedData + size <= diskSize) {
        storedData+=size;
        return true;
    }
    
    return false;
}

void CloudServer::free(uint32_t size) {
    int diff = storedData - size;
    storedData-=std::max(0, diff);
}

void CloudServer::printStats() {
    Computer::printStats();
    std::cout << "Stored Data:" << this->storedData << "\n" << std::endl;
}