
#include <algorithm>
#include <thrust/copy.h>

#include "thrust_nn_algorithm.h"

void ThrustNnAlgorithm::prepare(const PointCloud& pointcloud) {
    thrust::host_vector<CudaPoint> host(pointcloud.n_points());

    int i = 0;
    for(auto point : pointcloud) {
        host[i] = CudaPoint(point.x, point.y, point.z);
        i++;
    }

    points = host;
}

struct closest_point_op : public thrust::binary_function<CudaPoint, CudaPoint, CudaPoint> {
    CudaPoint operator()(const CudaPoint& p1, const CudaPoint& p2) {
        return CudaPoint();
    }
};

std::vector< std::pair<int, double> > ThrustNnAlgorithm::run() {
    return std::vector< std::pair<int, double> >();
}

std::string ThrustNnAlgorithm::name() const {
    return "Thrust GPU";
}
