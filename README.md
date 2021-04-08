# EXEN EXetended ENumerations for C++

- [EXEN EXetended ENumerations for C++](#exen-exetended-enumerations-for-c)
  - [Description](#description)
  - [How to](#how-to)
    - [Clone, Build, Test and Install](#clone-build-test-and-install)
    - [Create Enumeration with EXEN](#create-enumeration-with-exen)
      - [For CMake projects](#for-cmake-projects)
    - [Use Created Enumeration](#use-created-enumeration)
  - [Requires](#requires)
  - [Design Description](#design-description)
    - [The preprocessed ```Color.h```-file](#the-preprocessed-colorh-file)
      - [```Color.h```-file (without showing detail namespace)](#colorh-file-without-showing-detail-namespace)
      - [Full ```Color.h```-file (with detail namespace)](#full-colorh-file-with-detail-namespace)
  - [License](#license)

## Description

EXEN Exetended Enumerations is a header-only library, providing the possibility to create enumerations in C++ with compile-time (```constexpr```) enhancements.
Those enhancements are reflective information for example the last enumeration entry or the count of entries and so on. Enumerations created with EXEN also providing a string-converter for every enumeration-entry at compile-time (```constexpr```).

With the EXEN framework created enumerations the enumeration-type is optimized in memory consumption and therefore in less cache misses.
In case you have less than 256 enumeration entries it will deduct right size at compile time and choose for example in this case std::uint8_t. In case if there are more than 256 entries but less than 65536, it will deduct ```std::unit16_t```, and so on for the ```std::unit32_t``` and ```std::unit64_t```.

One more thing you get, it's possible to have the enumeration entries of a single enumeration in multiple files distributed. This enables for example to have at compile time a unique number for your components but not hardcoding them into the code upfront.

## How to

### Clone, Build, Test and Install
Clone the project from here: https://github.com/vahid-dzanic/exen

```bash
# clone
git clone https://github.com/vahid-dzanic/exen.git

# build
mkdir -p exen/build
cd exen/build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)

# test
ctest -j$(nproc)

# install
sudo make install
```

### Create Enumeration with EXEN
Let's say you want an enumeration for colors.
Create a file called Color.enum with following content:

```cpp
//Color.enum
__EXEN_ENTRY(RED)
__EXEN_ENTRY(GREEN)
__EXEN_ENTRY(BLUE)
```

Make sure that the Color.enum-file directory is in your buildsystems include-path.

Create a header-file Color.h which will contain the enum name (Color) and the needed include.
Define the name in the preprocessor variable ```__EXEN_ENUM_NAME Color```.
The name defined in ```__EXEN_ENUM_NAME``` must correlate to the *.enum filename, which in this case is ```Color```.

<b>Optionally</b> it's possible to define a ```namespace``` in which the enumeration and corresponding declarations will reside.
Therefore define the namespace in the preprocessor variable ```__EXEN_NAMESPACE``` after the ```__EXEN_ENUM_NAME``` definition.

After that, include ```exen/exen.h``` and that’s it.

```cpp
//Color.h
#pragma once
#define __EXEN_ENUM_NAME Color
#define __EXEN_NAMESPACE Car
#include "exen/exen.h"
```

EXEN is completely plain C++. There is NO need for any additional build steps or executing some magic scripts in the shell.

#### For CMake projects
In case your build system is CMake, you can setup the EXEN Header-only-libray as link-dependency and add the *.enum-file containing directories as include directories.

```
...

find_package(exen REQUIRED)

add_executable(my_app
  ...)

target_include_directories(my_app
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src/Color)

target_link_libraries(my_app
  PRIVATE
    vdc::exen
    ...
    ... )
```

### Use Created Enumeration

```cpp
//main.cpp
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
```

```bash
# console output
RED
GREEN
BLUE
----
GREEN
RED
BLUE
3
The underlying Type of color enum is std::uint8_t = true
```
## Requires
C++11 capable compiler

## Design Description
The library consists of one header file ```exen.h```. In order to use the header-file some preconditions has to be fulfilled.
* The filename where the ```__EXEN_ENTRY```'s are defined must correspond (case sensitive) to the ```__EXEN_ENUM_NAME``` defined name.
* The filename where the ```__EXEN_ENTRY```'s are defined must have the ```.enum``` extension
* There must be one or more ```__EXEN_ENTRY```'s defined.
* Directories with ```*.enum``` files must be declared in the build-systems include-path.
* Include the ```exen/exen.h```-header-file after the declarations ```__EXEN_ENUM_NAME``` and ```__EXEN_NAMESPACE```

The EXEN library uses the C++Preprocessor-Instructions to elaborate the potential count, the first and last entry or to get the string-representation.

The enumeration definition itself is within an identical named namespace in order to distinguish the helper functions between multiple EXEN-created-enumerations.

Within this namespace there is another namespace called ```detail```. Within this namespace are some helper declarations which are probably not useful for the user.

Optionally it's possible to define a ```namespace``` with ```__EXEN_NAMESPACE``` in which all declarations will reside.

The EXEN enumerations can be converted to string with the provided function ```name``` where the enumeration-entry has to be passed as attribute. And in addition the operator ```<<``` is overloaded for the string stream operations.

### The preprocessed ```Color.h```-file

In case your using ```gcc``` compiler, with adding the compile options ```-E``` and ```-P```, the compiler will output just the preprocessed file.

This is quite handy if you want to debug or just to see how the enumerator is defined.

#### ```Color.h```-file (without showing detail namespace)
```cpp
...

namespace Car {
namespace Color {

constexpr std::uint64_t count() { return static_cast<std::uint64_t>(detail::private_Color::COUNT); }

enum Color : detail::optimal_unsigned_integer_size_type
{
RED,
GREEN,
BLUE,
};
constexpr std::array<Color, count()> array() {
  return std::array<Color, count()>{{
Color::RED,
Color::GREEN,
Color::BLUE,
  }};
}
constexpr Color first() {
  return static_cast<Color>(0);
}
constexpr Color last() {
  return static_cast<Color>(count() - 1);
}

constexpr const char* name(Color value) {
  return detail::enum_names[static_cast<std::uint64_t>(value)];
}
}
}
std::ostream& operator<<(std::ostream& stream, Car::Color::Color rhs)
{
  stream << std::string(Car::Color::name(rhs));
  return stream;
}

...
```

#### Full ```Color.h```-file (with detail namespace)
```cpp
...

namespace Car {
namespace Color {
namespace detail {
enum class private_Color
{
RED,
GREEN,
BLUE,
  COUNT
};
}
constexpr std::uint64_t count() { return static_cast<std::uint64_t>(detail::private_Color::COUNT); }
namespace detail {
static_assert(count() != 0,
              "There are no enumerator entries in the \"Color.enum\" file");
using optimal_unsigned_integer_size_type =
  std::conditional<std::numeric_limits<std::uint8_t>::max() >= count(), std::uint8_t,
    std::conditional<std::numeric_limits<std::uint16_t>::max() >= count(), std::uint16_t,
      std::conditional<std::numeric_limits<std::uint32_t>::max() >= count(), std::uint32_t,
        std::uint64_t
      >::type
    >::type
  >::type;
}
enum Color : detail::optimal_unsigned_integer_size_type
{
RED,
GREEN,
BLUE,
};
constexpr std::array<Color, count()> array() {
  return std::array<Color, count()>{{
Color::RED,
Color::GREEN,
Color::BLUE,
  }};
}
constexpr Color first() {
  return static_cast<Color>(0);
}
constexpr Color last() {
  return static_cast<Color>(count() - 1);
}
namespace detail {
constexpr std::array<const char*, count()> enum_names =
{{
"RED",
"GREEN",
"BLUE",
}};
}
constexpr const char* name(Color value) {
  return detail::enum_names[static_cast<std::uint64_t>(value)];
}
}
}
std::ostream& operator<<(std::ostream& stream, Car::Color::Color rhs)
{
  stream << std::string(Car::Color::name(rhs));
  return stream;
}

...
```

## License
Mozilla Public License Version 2.0
