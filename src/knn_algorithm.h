#ifndef KNN_ALGORITHM_H
#define KNN_ALGORITHM_H

#include "pointcloud.h"
#include "point.h"

class KnnAlgorithm {
public:
    virtual void init(const PointCloud& pointcloud)=0;
    virtual std::pair<int, double> run(const Point& point)=0;
};

#endif
