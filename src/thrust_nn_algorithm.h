#ifndef THRUST_NN_ALGORITHM
#define THRUST_NN_ALGORITHM

#include <thrust/device_vector.h>

#include "cuda_point.h"
#include "nn_algorithm.h"

class ThrustNnAlgorithm : public NnAlgorithm {
public:
    void prepare(const PointCloud& pointcloud);
    std::vector< std::pair<int, double> > run();
    std::string name() const;
private:
    thrust::device_vector<CudaPoint> points;
};

#endif
