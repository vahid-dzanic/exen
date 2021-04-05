cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(heroes VERSION 1.0.0 LANGUAGES CXX)

find_package(exen REQUIRED)

set(HEADER_FILES
  src/heroes/Hero.h
  src/heroes/Hero.enum
  src/heroes/DC.enum
  src/heroes/Marvel.enum)

add_executable(${PROJECT_NAME}
  ${HEADER_FILES}
  src/main.cpp)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
    VERSION "${PROJECT_VERSION}")

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src/heroes)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    vdc::exen)
