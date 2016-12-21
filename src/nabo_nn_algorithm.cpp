
#include "point.h"
#include "nabo_nn_algorithm.h"

NaboNnAlgorithm::NaboNnAlgorithm() : m(), nns(NULL) {}

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
