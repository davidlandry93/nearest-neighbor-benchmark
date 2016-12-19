
#include <gflags/gflags.h>

#include <iostream>
#include <nabo/nabo.h>

#include "pointcloud.h"

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

    return 0;
}
