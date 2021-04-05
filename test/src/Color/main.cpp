// README.md example

#include "Color.h"
#include <iostream>
#include <type_traits>

int main(int, char**)
{
  for (auto value : Car::Color::array())
  {
    std::cout << value << "\n";
  }
  std::cout << "----" << "\n";

  auto green = Car::Color::GREEN;

  std::string str = Car::Color::name(green);
  std::cout << str << "\n";
  std::cout << Car::Color::first() << "\n";
  std::cout << Car::Color::last() << "\n";
  std::cout << Car::Color::count() << "\n";

  constexpr bool COLOR_IS_UINT8 =
    std::is_same<std::underlying_type_t<decltype(green)>,
                 std::uint8_t>::value;

  std::cout << "The underlying Type of color enum is std::uint8_t = "
            << std::boolalpha << COLOR_IS_UINT8 << "\n";

  return 0;
}
