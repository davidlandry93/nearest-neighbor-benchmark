cmake_minimum_required(VERSION 3.0)

project(nearest-neighbor-benchmark)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

find_package(Eigen3 REQUIRED)
find_package(libnabo REQUIRED)
find_package(VTK REQUIRED)
find_package(gflags REQUIRED)

include_directories(src include ${EIGEN3_INCLUDE_DIR} ${VTK_INCLUDE_DIRS})

file(GLOB SOURCES src/*.cpp)
add_executable(benchmark ${SOURCES})
target_link_libraries(benchmark nabo ${VTK_LIBRARIES} gflags)
