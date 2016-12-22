#ifndef THRUST_REDUCE_KEY_NN_ALGORITHM_H
#define THRUST_REDUCE_KEY_NN_ALGORITHM_H

#include <thrust/device_vector.h>

#include "cuda_point.h"
#include "nn_algorithm.h"

class ThrustReduceKeyNnAlgorithm : public NnAlgorithm {
public:
    void prepare(const PointCloud& pointcloud);
    std::vector< std::pair<int, double> > run();
    std::string name() const;
private:
    thrust::device_vector<CudaPoint> points;
};

#endif
