
#include <vtkSmartPointer.h>
#include <vtkGenericDataObjectReader.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>

#include "pointcloud.h"

PointCloud::PointCloud(const std::vector<Point>& points) : points(std::move(points)) {}

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

    return PointCloud(points);
}
