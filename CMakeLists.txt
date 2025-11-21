cmake_minimum_required(VERSION 3.16)

project(BlackJackSolver CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Global C++ settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-function -O2)

# Add player subdirectory
file(GLOB PLAYER_DIRS "${CMAKE_SOURCE_DIR}/*/black_jack_solver.cpp")
foreach(PLAYER_CPP ${PLAYER_DIRS})
  get_filename_component(PLAYER_DIR ${PLAYER_CPP} DIRECTORY)
  get_filename_component(PLAYER_NAME ${PLAYER_DIR} NAME)
  add_subdirectory(${PLAYER_NAME})
endforeach()
