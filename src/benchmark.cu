
#include <gflags/gflags.h>

#include <iostream>
#include <chrono>

#include "pointcloud.h"
#include "nn_algorithm.h"
#include "nabo_nn_algorithm.h"
#include "thrust_nn_algorithm.h"

DEFINE_string(input, "", "Path to the vtk file to load.");

int main(int argc, char** argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    std::string usage("Run hierarchical expectation-maximization on a point cloud.\n");
    usage += argv[0];
    usage +=  + " -input pcl.vtk -output out.csv -vtk";

    if(FLAGS_input.empty()) {
        std::cout << "No input pointcloud provided." << std::endl;
        return 0;
    }

    PointCloud pointcloud = PointCloud::from_vtk(FLAGS_input);

    std::vector< std::unique_ptr<NnAlgorithm> > algorithms;
    algorithms.push_back(std::unique_ptr<NnAlgorithm>(new NaboNnAlgorithm()));
    algorithms.push_back(std::unique_ptr<NnAlgorithm>(new ThrustNnAlgorithm()));

    for(auto&& algorithm : algorithms) {
        std::cout << "Copying data for " << algorithm->name() << "..." << std::endl;
        auto start = std::chrono::steady_clock::now();
        algorithm->prepare(pointcloud);
        std::cout << "Took " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;

        std::cout << "Running " << algorithm->name() << "..." << std::endl;
        start = std::chrono::steady_clock::now();
        auto solution = algorithm->run();
        std::cout << "Took " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;


        // for(auto pair : solution) {
        //     std::cout << pair.first << " " << pair.second << std::endl;
        // }
    }

    return 0;
}
