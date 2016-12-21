cmake_minimum_required(VERSION 3.0)

project(nearest-neighbor-benchmark)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

find_package(Eigen3 REQUIRED)
find_package(libnabo REQUIRED)
find_package(VTK REQUIRED)
find_package(gflags REQUIRED)
find_package(CUDA REQUIRED)

include_directories(src include ${EIGEN3_INCLUDE_DIR} ${VTK_INCLUDE_DIRS})

list(APPEND CUDA_NVCC_FLAGS "-arch=sm_30;-std=c++11")

set(CPP_SOURCES src/nabo_nn_algorithm.cpp src/pointcloud.cpp)
add_library(benchmark_cpp_lib ${CPP_SOURCES})
target_link_libraries(benchmark_cpp_lib
  nabo
  gomp
  ${VTK_LIBRARIES}
  gflags)

set(CUDA_SOURCES src/benchmark.cu src/thrust_nn_algorithm.cu)
cuda_add_executable(benchmark ${CUDA_SOURCES})
target_link_libraries(benchmark benchmark_cpp_lib ${CUDA_LIBRARIES})
