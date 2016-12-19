#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include <string>
#include <vector>

#include "point.h"

class PointCloud {
public:
    typedef std::vector<Point>::const_iterator PointIterator;

    PointCloud(const std::vector<Point>& points, const Point& min, const Point& max);
    PointIterator begin() const;
    PointIterator end() const;

    static PointCloud from_vtk(const std::string& path);

private:
    std::vector<Point> points;
    Point min, max;
};


#endif
