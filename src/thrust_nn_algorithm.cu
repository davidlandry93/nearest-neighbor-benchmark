
#include "thrust_nn_algorithm.h"

void ThrustNnAlgorithm::prepare(const PointCloud& pointcloud) {
    points.reserve(pointcloud.n_points());

    for(auto point : pointcloud) {
        points.push_back(CudaPoint(point.x, point.y, point.z));
    }
}

std::vector< std::pair<int, double> > ThrustNnAlgorithm::run() {
    return std::vector< std::pair<int, double> >();
}

std::string ThrustNnAlgorithm::name() const {
    return "Thrust GPU";
}
