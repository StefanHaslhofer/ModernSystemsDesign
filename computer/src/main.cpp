#include <iostream>

#include "computer.hpp"

int main() {
  Computer comp("Computer 1", 4, 1024);

  comp.printStats();
  comp.start(10);
}
