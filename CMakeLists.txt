cmake_minimum_required(VERSION 3.12.4)
project(Starfield_SDL2)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
add_subdirectory(external/random)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp Star.cpp Star.hpp)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} effolkronium_random)
