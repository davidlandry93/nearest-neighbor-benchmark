
#include "point.h"
#include "nabo_nn_algorithm.h"

NaboNnAlgorithm::NaboNnAlgorithm() : m(){}

void NaboNnAlgorithm::prepare(const PointCloud& pointcloud) {
    m.resize(3, pointcloud.n_points());

    int i=0;
    for(Point point : pointcloud) {
        m(0,i) = point.x;
        m(1,i) = point.y;
        m(2,i) = point.z;

        i++;
    }
}

std::vector< std::pair<int, double> > NaboNnAlgorithm::run() {
    // Build the kd-tree.
    std::unique_ptr<Nabo::NNSearchD> tree(Nabo::NNSearchD::createKDTreeLinearHeap(m));

    std::vector< std::pair<int, double> > nearest_neighbors;
    for(int i = 0; i < m.cols(); i++) {
        Eigen::VectorXi index(1);
        Eigen::VectorXd distance(1);

        tree->knn(m.col(i), index, distance, 1);

        nearest_neighbors.push_back(std::make_pair(index(0,0), distance(0,0)));
    }

    return nearest_neighbors;
}

std::string NaboNnAlgorithm::name() const {
    return "libnabo";
}
