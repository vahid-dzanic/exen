#include "Hero.h"

#include <iostream>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
  std::cout << "List of all heroes so far: " << "\n";
  std::cout << "---------------------------" << "\n";
  for (auto hero : md::Hero::array())
  {
    std::cout << hero << "\n";
  }
  std::cout << "---------------------------" << "\n";
  return 0;
}
