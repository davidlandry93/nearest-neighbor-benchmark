#ifndef NN_ALGORITHM_H
#define NN_ALGORITHM_H

#include <string>

#include "pointcloud.h"
#include "point.h"

class NnAlgorithm {
public:
    // Do the data copies before running the algorithm.
    virtual void prepare(const PointCloud& pointcloud)=0;

    // Run the algorithm.
    virtual std::vector< std::pair<int, double> > run()=0;

    virtual std::string name() const=0;
};

#endif
