cmake_minimum_required(VERSION 3.16)
project(DupeDetect)

set(CMAKE_CXX_STANDARD 17)

if(NOT MSVC)
    find_package(TBB)
endif()

add_executable(DupeDetect main.cpp Blake3Hash.cpp RecursiveDuplicateFinder.cpp Options.cpp StringUtils.cpp DepthLimitedDuplicateFinder.cpp DepthLimitedDuplicateFinder.h DuplicateFinder.h DuplicateFindUtils.h)
add_subdirectory(BLAKE3)

target_link_libraries(DupeDetect BLAKE3)

if(NOT MSVC)
    target_link_libraries(DupeDetect TBB)
endif()