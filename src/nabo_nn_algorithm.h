#ifndef NABO_NN_ALGORITHM_H
#define NABO_NN_ALGORITHM_H

#include <nabo/nabo.h>

#include "pointcloud.h"
#include "nn_algorithm.h"

class NaboNnAlgorithm : public NnAlgorithm {
public:
    NaboNnAlgorithm();
    void prepare(const PointCloud& pointcloud);
    std::vector< std::pair<int, double> > run();
private:
    Eigen::MatrixXd m;
    std::unique_ptr<Nabo::NNSearchF> nns;

    void init(const PointCloud& pointcloud);
};

#endif
