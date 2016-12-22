
#include <thrust/iterator/counting_iterator.h>
#include <thrust/iterator/permutation_iterator.h>

#include "thrust_reduce_key_nn_algorithm.h"

void ThrustReduceKeyNnAlgorithm::prepare(const PointCloud& pointcloud) {
    thrust::host_vector<CudaPoint> host_points(pointcloud.n_points());

    int i = 0;
    for(auto point : pointcloud) {
        host_points[i++] = CudaPoint(point.x, point.y, point.z);
    }

    points = host_points;
}

struct divide_by_constant_op : thrust::unary_function<int,int> {
    __const__ int denominator;

    divide_by_constant_op(int denominator) : denominator(denominator) {}

    int operator()(int numerator) {
        return numerator / denominator;
    }
};

struct modulus_constant_op : thrust::unary_function<int,int> {
    __const__ int modulus;

    modulus_constant_op(int modulus) : modulus(modulus) {}

    int operator()(int n) {
        return n % modulus;
    }
};

struct distance_of_points_op : thrust::unary_function< thrust::tuple<CudaPoint,CudaPoint>, double > {
    double operator()(thrust::tuple<CudaPoint,CudaPoint> pair) {
        CudaPoint lhs = thrust::get<0>(pair);
        CudaPoint rhs = thrust::get<1>(pair);

        return (lhs.x - rhs.x) * (lhs.x - rhs.x) +
            (lhs.y - rhs.y) * (lhs.x - rhs.y) +
            (lhs.z - rhs.z) * (lhs.x - rhs.z);
    }
};

std::vector< std::pair<int, double> > ThrustReduceKeyNnAlgorithm::run() {
    thrust::counting_iterator<int> n_couples_evaluated_begin(0);
    thrust::counting_iterator<int> n_couples_evaluated_end(points.size() * points.size());

    thrust::reduce(n_couples_evaluated_begin, n_couples_evaluated_end);

    auto reduction_key_iterator_begin = thrust::make_transform_iterator(n_couples_evaluated_begin, divide_by_constant_op(points.size()));
    auto reduction_key_iterator_end = thrust::make_transform_iterator(n_couples_evaluated_end, divide_by_constant_op(points.size()));

    // thrust::reduce(reduction_key_iterator_begin, reduction_key_iterator_end);

    auto point_index_iterator_begin = thrust::make_transform_iterator(n_couples_evaluated_begin, modulus_constant_op(points.size()));
    auto point_index_iterator_end = thrust::make_transform_iterator(n_couples_evaluated_end, modulus_constant_op(points.size()));

    auto lhs_point_iterator_begin = thrust::make_permutation_iterator(points.begin(), reduction_key_iterator_begin);
    auto rhs_point_iterator_begin = thrust::make_permutation_iterator(points.begin(), point_index_iterator_begin);

    auto lhs_point_iterator_end = thrust::make_permutation_iterator(points.end(), reduction_key_iterator_end);
    auto rhs_point_iterator_end = thrust::make_permutation_iterator(points.end(), point_index_iterator_end);

    auto point_combinations_begin = thrust::make_zip_iterator(thrust::make_tuple(lhs_point_iterator_begin, rhs_point_iterator_begin));
    auto point_combinations_end = thrust::make_zip_iterator(thrust::make_tuple(lhs_point_iterator_end, rhs_point_iterator_end));

    auto distances_of_pairs_begin = thrust::make_transform_iterator(point_combinations_begin, distance_of_points_op());
    auto distances_of_pairs_end = thrust::make_transform_iterator(point_combinations_end, distance_of_points_op());

    thrust::device_vector<int> keys(points.size());
    thrust::device_vector<double> nearest_neighbors(points.size());

    // thrust::reduce(distances_of_pairs_begin, distances_of_pairs_end);

    // thrust::reduce_by_key(reduction_key_iterator_begin, reduction_key_iterator_end,
    //                       distances_of_pairs, keys.begin(), nearest_neighbors.begin());

    std::vector< std::pair<int, double> > host_nearest_neighbors;
    return host_nearest_neighbors;
}

std::string ThrustReduceKeyNnAlgorithm::name() const {
    return "Thrust GPU, Reduce by key.";
}
