
#include <vtkSmartPointer.h>
#include <vtkGenericDataObjectReader.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>

#include "pointcloud.h"

PointCloud::PointCloud(const std::vector<Point>& points, const Point& min, const Point& max) : points(std::move(points)), min(min), max(max) {}

PointCloud::PointIterator PointCloud::begin() const {
    return points.begin();
}

PointCloud::PointIterator PointCloud::end() const {
    return points.end();
}

PointCloud PointCloud::from_vtk(const std::string& filename) {
    auto reader = vtkSmartPointer<vtkGenericDataObjectReader>::New();
    reader->SetFileName(filename.c_str());
    reader->Update();

    auto polydata = vtkSmartPointer<vtkPolyData>(reader->GetPolyDataOutput());

    auto n_points = polydata->GetNumberOfPoints();
    auto vtk_points = vtkSmartPointer<vtkPoints>(polydata->GetPoints());

    double current_point[3];
    std::vector<Point> points(n_points);
    for(int i=0; i < n_points; i++) {
        vtk_points->GetPoint(i, current_point);

        points[i].x = current_point[0];
        points[i].y = current_point[1];
        points[i].z = current_point[2];
    }

    double bounds[6];
    vtk_points->GetBounds(bounds);

    return PointCloud(points, Point(bounds[0], bounds[2], bounds[4]), Point(bounds[1], bounds[3], bounds[5]));
}
