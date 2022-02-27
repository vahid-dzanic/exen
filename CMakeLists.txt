# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(exen VERSION 2.2.0 LANGUAGES CXX)

option(ENABLE_TESTING "Build all tests too, ON by default" ON)

set(ALIAS_TARGET_NAME "vdc")
set(HEADER_FILES
  include/${PROJECT_NAME}/exen.h)

add_library(${PROJECT_NAME} INTERFACE
  ${HEADER_FILES})
add_library(${ALIAS_TARGET_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}
  PROPERTIES
    PUBLIC_HEADER "${HEADER_FILES}"
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}")

target_include_directories(${PROJECT_NAME}
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

target_compile_features(${PROJECT_NAME}
  INTERFACE
    cxx_std_17)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-config
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  PUBLIC_HEADER DESTINATION include/${PROJECT_NAME})
configure_file(${PROJECT_SOURCE_DIR}/config/config.cmake ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake @ONLY)
install(FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake DESTINATION cmake)

if (ENABLE_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()
