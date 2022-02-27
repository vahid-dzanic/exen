cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

find_package(GTest REQUIRED)

add_executable(colors_test
  src/Color/Color.h
  src/Color/Color2.h
  src/Color/Color.enum
  src/Color/Color2.enum
  src/Color/colors.cpp
  src/Color/colors2.cpp)

# target_compile_options(colors_test
#  PRIVATE
#   -E
#   -P)

target_include_directories(colors_test
  PRIVATE
    ${PROJECT_SOURCE_DIR}/test/src/Color)

target_link_libraries(colors_test
  PRIVATE
    ${PROJECT_NAME}
    gtest
    gmock
    gtest_main
    pthread)

add_test(colors_test colors_test)


add_executable(colors_example
  src/Color/Color.h
  src/Color/Color.enum
  src/Color/main.cpp)

target_include_directories(colors_example
  PRIVATE
    ${PROJECT_SOURCE_DIR}/test/src/Color)

target_link_libraries(colors_example
  PRIVATE
    ${PROJECT_NAME})

add_executable(car_test
  src/Car/Car.h
  src/Car/Car.hpp
  src/Car/Car.cpp)

target_include_directories(car_test
  PRIVATE
    ${PROJECT_SOURCE_DIR}/test/src)

#target_compile_options(car_test
# PRIVATE
#  -E
#  -P)

target_link_libraries(car_test
  PRIVATE
    ${PROJECT_NAME}
    gtest
    gmock
    gtest_main
    pthread)

add_test(car_test car_test)
