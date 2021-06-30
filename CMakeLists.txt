cmake_minimum_required(VERSION 3.16)
project(DupeDetect)

set(CMAKE_CXX_STANDARD 17)

if(LINUX)
    find_package(TBB REQUIRED)
endif()

add_executable(DupeDetect main.cpp Blake3Hash.cpp RecursiveDuplicateFinder.cpp Options.cpp StringUtils.cpp DepthLimitedDuplicateFinder.cpp DepthLimitedDuplicateFinder.h DuplicateFindUtils.h Size.cpp DuplicateFindUtils.cpp ParallelWrapper.h)
add_subdirectory(BLAKE3)

target_link_libraries(DupeDetect BLAKE3)

if(LINUX)
    target_link_libraries(DupeDetect TBB)
endif()