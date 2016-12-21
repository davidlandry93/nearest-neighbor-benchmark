#ifndef NN_ALGORITHM_H
#define NN_ALGORITHM_H

#include "pointcloud.h"
#include "point.h"

class NnAlgorithm {
public:
    // Do the data copies before running the algorithm.
    virtual void prepare()=0;

    // Run the algorithm.
    virtual std::vector< std::pair<int, double> > run(const PointCloud& pointcloud)=0;
};

#endif
