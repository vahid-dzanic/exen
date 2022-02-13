# EXEN EXtended ENumerations for C++

- [EXEN EXtended ENumerations for C++](#exen-extended-enumerations-for-c)
  - [Description](#description)
  - [How to](#how-to)
    - [Clone, Build, Test and Install](#clone-build-test-and-install)
    - [Create Enumeration with EXEN](#create-enumeration-with-exen)
      - [For CMake projects](#for-cmake-projects)
    - [Use Created Enumeration](#use-created-enumeration)
  - [Types and Functions provided with EXEN enumerations](#types-and-functions-provided-with-exen-enumerations)
  - [Requires](#requires)
  - [Design Description](#design-description)
    - [The preprocessed ```Color.h```-file](#the-preprocessed-colorh-file)
      - [```Color.h```-file (without showing detail namespace)](#colorh-file-without-showing-detail-namespace)
      - [Full ```Color.h```-file (with detail namespace)](#full-colorh-file-with-detail-namespace)
  - [License](#license)
  - [Presentation](#presentation)

## Description

EXEN Extended Enumerations is a header-only library, providing the possibility to create enumerations in C++ with compile-time (```constexpr```) enhancements.
Those enhancements are reflective information for example the last enumeration entry or the count of entries and so on. Enumerations created with EXEN also providing a string-converter for every enumeration-entry at compile-time (```constexpr```).

With the EXEN framework created enumerations the enumeration-type is optimized in memory consumption and therefore in less cache misses.

<b>EXEN Version 1.0.0:</b>
In case you have less than 256 enumeration entries it will deduct right size at compile time and choose for example in this case std::uint8_t. In case if there are more than 256 entries but less than 65536, it will deduct ```std::unit16_t```, and so on for the ```std::unit32_t``` and ```std::unit64_t```.

<b>EXEN Version 2.0.0:</b>
In the version 2.0.0 it's possible to define a value for each entry, with this the data type is deduced with the maximum value instead of using the number of entries.

One more thing you get, it's possible to have the enumeration entries of a single enumeration in multiple files distributed. This enables for example to have at compile time a unique number for your components but not hard-coding them into the code upfront.

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
__EXEN_ENUM_ENTRY(RED)
__EXEN_ENUM_ENTRY(GREEN, 7)
__EXEN_ENUM_ENTRY(BLUE)
```

Create an entry with the ```__EXEN_ENUM_ENTRY``` declaration.

<b>EXEN Version 2.0.0:</b> If an entry has to have a special value defined, just add the value separated from the entry-name with comma to the ```__EXEN_ENUM_ENTRY``` declaration (e.g ```__EXEN_ENUM_ENTRY(GREEN, 7)```).

Make sure that the Color.enum-file directory is in your build-systems include-path.

Create a header-file Color.h which will contain the enum name (Color) and the needed include.
Define the name in the preprocessor variable ```__EXEN_ENUM_NAME Color```.
The name defined in ```__EXEN_ENUM_NAME``` must correlate to the *.enum filename, which in this case is ```Color```.

<b>Optionally</b> it's possible to define a ```namespace``` in which the enumeration and corresponding declarations will reside.
Therefore define the namespace in the preprocessor variable ```__EXEN_NAMESPACE```.

<b>Optionally</b> since <b>EXEN Version 2.1.0:</b> it's possible to define a prefix for the entry names without changing the string representation of it.
Define the entry name prefix in the preprocessor variable ```__EXEN_ENTRY_PREFIX```.

After that, include ```exen/exen.h``` and that’s it.

```cpp
//Color.h
#pragma once
#define __EXEN_NAMESPACE Car
#define __EXEN_ENUM_NAME Color
#define __EXEN_ENTRY_PREFIX k
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

  auto green = Car::Color::kGREEN;

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
## Types and Functions provided with EXEN enumerations
The enumeration-declaration itself depending on the defined __EXEN_ENUM_NAME name and optionally the defined __EXEN_NAMESPACE name (e.g. ```[enumeration type] --> e.g. Car::Color::Color```)
```c++
// Returning a predefined std::array with the enumeration entries
constexpr std::array<[enumeration type], [entry count]> array()

// Returning the first entry of the enumeration
constexpr [enumeration type] first()

// Returning the last entry of the enumeration
constexpr [enumeration type] last()

// Returning the enumeration entry with the smallest value
// since EXEN Version 2.0.0
constexpr [enumeration type] min() 

// Returning the enumeration entry with the biggest value
// since EXEN Version 2.0.0
constexpr [enumeration type] max()

// Returning enumeration entry count
constexpr std::uint64_t count()

// Returning the enumeration-type name with namespace as string
// since EXEN Version 2.0.0
constexpr std::string_view type_name()

// Returning the string representation of the given enumeration entry
constexpr std::string_view name([enumeration type] entry)
```

## Requires
<b>EXEN Version 1.0.0:</b>
C++11 capable compiler

<b>EXEN Version 2.0.0:</b>
C++17 capable compiler

## Design Description
The library consists of one header file ```exen.h```. In order to use the header-file some preconditions has to be fulfilled.
* The filename where the ```__EXEN_ENUM_ENTRY```'s are defined must correspond (case sensitive) to the ```__EXEN_ENUM_NAME``` defined name.
* The filename where the ```__EXEN_ENUM_ENTRY```'s are defined must have the ```.enum``` extension
* There must be one or more ```__EXEN_ENUM_ENTRY```'s defined.
* Directories with ```*.enum``` files must be declared in the build-systems include-path.
* Include the ```exen/exen.h```-header-file after the declarations ```__EXEN_ENUM_NAME```, ```__EXEN_NAMESPACE``` and ```__EXEN_ENTRY_PREFIX```

The EXEN library uses the C++Preprocessor-Instructions to elaborate the potential count, the first and last entry or to get the string-representation.

The enumeration definition itself is within an identical named namespace in order to distinguish the helper functions between multiple EXEN-created-enumerations.

Within this namespace there is another namespace called ```detail```. Within this namespace are some helper declarations which are probably not useful for the user.

Optionally it's possible to define a ```namespace``` with ```__EXEN_NAMESPACE``` in which all declarations will reside.

The EXEN enumerations can be converted to string with the provided function ```name``` where the enumeration-entry has to be passed as attribute. And in addition the operator ```<<``` is overloaded for the string stream operations.

### The preprocessed ```Color.h```-file

In case your using ```gcc``` compiler, with adding the compile options ```-E``` and ```-P```, the compiler will output just the preprocessed file.

This is quite handy if you want to debug or just to see how the enumerator is defined.

#### ```Color.h```-file (without showing detail namespace)
```c++
...

namespace Car {
namespace Color {

enum Color : detail::optimal_unsigned_integer_size_type
{
kRED = 0,
kGREEN = 1,
kBLUE = 55000,
kORANGE,
};

constexpr auto array() {
  return detail::private_array;
}
constexpr Color first() {
  return array().front();
}
constexpr Color last() {
  return array().back();
}
constexpr Color min() {
  return static_cast<Color>(detail::min);
}
constexpr Color max() {
  return static_cast<Color>(detail::max);
}
constexpr std::uint64_t count() { return array().size(); }
constexpr std::string_view type_name() {
  return std::string_view("Car::Color");
}

constexpr std::string_view name(Color entry) {
  return detail::enum_names[detail::index_of(array(), entry)];
}
}
}
std::ostream& operator<<(std::ostream& stream, Car::Color::Color rhs)
{
  stream << Car::Color::name(rhs);
  return stream;
}

...
```

#### Full ```Color.h```-file (with detail namespace)
```c++
...

namespace Car {
namespace Color {
namespace detail {
enum class private_Color
{
kRED = 0,
kGREEN = 1,
kBLUE = 55000,
kORANGE,
};
constexpr auto min = std::min({
private_Color::kRED,
private_Color::kGREEN,
private_Color::kBLUE,
private_Color::kORANGE,
  });
constexpr auto max = std::max({
private_Color::kRED,
private_Color::kGREEN,
private_Color::kBLUE,
private_Color::kORANGE,
  });
using optimal_unsigned_integer_size_type =
  std::conditional<std::numeric_limits<std::uint8_t>::max() >= static_cast<std::uint64_t>(max), std::uint8_t,
    std::conditional<std::numeric_limits<std::uint16_t>::max() >= static_cast<std::uint64_t>(max), std::uint16_t,
      std::conditional<std::numeric_limits<std::uint32_t>::max() >= static_cast<std::uint64_t>(max), std::uint32_t,
        std::uint64_t
      >::type
    >::type
  >::type;
}
enum Color : detail::optimal_unsigned_integer_size_type
{
kRED = 0,
kGREEN = 1,
kBLUE = 55000,
kORANGE,
};
namespace detail {
constexpr std::array private_array{
Color::kRED,
Color::kGREEN,
Color::kBLUE,
Color::kORANGE,
  };
}
constexpr auto array() {
  return detail::private_array;
}
constexpr Color first() {
  return array().front();
}
constexpr Color last() {
  return array().back();
}
constexpr Color min() {
  return static_cast<Color>(detail::min);
}
constexpr Color max() {
  return static_cast<Color>(detail::max);
}
constexpr std::uint64_t count() { return array().size(); }
constexpr std::string_view type_name() {
  return std::string_view("Car::Color");
}
namespace detail {
static_assert(count() != 0,
              "There are no enumerator entries in the \"Color.enum\" file");
template<typename _Tp>
constexpr inline bool unique_entries(const _Tp array) {
  for (std::size_t outer = 1; outer < array.size(); ++outer) {
    for (std::size_t inner = 0; inner < outer; ++inner) {
      if (array[outer] == array[inner]) {
        return false;
      }
    }
  }
  return true;
}
static_assert(unique_entries(array()),
              "The enumerator entries must be unique: check enum Car::Color");
constexpr auto enum_names = std::array {
std::string_view("RED"),
std::string_view("GREEN"),
std::string_view("BLUE"),
std::string_view("ORANGE"),
};
template<typename _Tp>
constexpr inline std::size_t index_of(_Tp array, const Car::Color::Color val) {
  for(std::size_t idx = 0; idx < array.size(); ++idx) {
    if (array[idx] == val) {
      return idx;
    }
  }
  return -1;
}
}
constexpr std::string_view name(Color entry) {
  return detail::enum_names[detail::index_of(array(), entry)];
}
}
}
std::ostream& operator<<(std::ostream& stream, Car::Color::Color rhs)
{
  stream << Car::Color::name(rhs);
  return stream;
}

...
```

## License
Mozilla Public License Version 2.0

## Presentation
[github pages](https://vahid-dzanic.github.io/exen)
