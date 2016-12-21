#ifndef CUDA_POINT_H
#define CUDA_POINT_H

struct CudaPoint {
    double x,y,z;

    __host__ __device__
    CudaPoint() : x(0.0), y(0.0), z(0.0) {}
    __host__ __device__
    CudaPoint(double x, double y, double z) : x(x), y(y), z(z) {}
};

#endif
