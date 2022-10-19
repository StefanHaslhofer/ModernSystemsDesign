#include <iostream>

#include "computer.hpp"
#include "cloudServer.hpp"
#include "cloud.hpp"

int main() {
  Cloud c;

  unsigned int id = c.add("168.92.51.30", "Computer 1", 4, 1024);
  unsigned int id2 = c.add("168.92.51.31", "Computer 2", 8, 2048);

  std::cout << "# Servers:" << c.servers.size() << "\n" << std::endl;
  //c.remove(id2);
  //std::cout << "# Servers:" << c.servers.size() << "\n" << std::endl;

  c.start(10);
}
