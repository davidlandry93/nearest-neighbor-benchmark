#ifndef NABO_NN_ALGORITHM_H
#define NABO_NN_ALGORITHM_H

#include <memory>
#include <nabo/nabo.h>

#include "pointcloud.h"
#include "nn_algorithm.h"

class NaboNnAlgorithm : public NnAlgorithm {
public:
    NaboNnAlgorithm();
    std::string name() const;
    void prepare(const PointCloud& pointcloud);
    std::vector< std::pair<int, double> > run();
private:
    Eigen::MatrixXd m;

    void init(const PointCloud& pointcloud);
};

#endif
