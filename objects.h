#pragma once

#include <vector>

#define PI 3.14159265359
#define RAD(x) x * PI / 180
#define DEG(x) x * 180 / PI
#define SGN(x) ((x > 0) - (x < 0))

//  horizontal line class
class Horizontal_Line
{
public:
    double y;
public:
    Horizontal_Line(double y = 0);
};
//  vertical line class
class Vertical_Line
{
public:
    double x;
public:
    Vertical_Line(double x = 0);
};

//  2D point class
class Point_2D
{
public:
    double x, y;
public:
    Point_2D(double x = 0, double y = 0);
};
//  3D point class
class Point_3D
{
public:
    double x, y, z;
public:
    Point_3D(double x = 0, double y = 0, double z = 0);

    void move(double x, double y, double z);
    void move(Point_3D vector);
};
//  2D line index class
class Line_2D_Indices {
public:
    int point_1, point_2;
public:
    Line_2D_Indices(int point_1 = 0, int point_2 = 0);
};
//  2D line class
class Line_2D {
public:
    Point_2D point_1, point_2;
public:
    Line_2D(Point_2D point_1 = Point_2D(-1, -1), Point_2D point_2 = Point_2D(1, 1));
};
//  3D line class
class Line_3D {
public:
    Point_3D point_1, point_2;
public:
    Line_3D(Point_3D point_1 = Point_3D(-1, -1, -1), Point_3D point_2 = Point_3D(1, 1, 1));
};

//  3D object class
class Object_3D
{
protected:
    Point_3D position;
    Point_3D rotation;
    bool ifLines;
    std::vector<Point_3D> points;
    std::vector<Line_2D_Indices> linesIndices;
public:
    Object_3D(std::vector<Point_3D> points = {}, Point_3D position = Point_3D(0, 0, 0), Point_3D rotation = Point_3D(0, 0, 0), std::vector<Line_2D_Indices> linesIndices = {}, bool ifLines = true);

    Point_3D getPosition();
    Point_3D getRotation();

    std::vector<Point_3D> normalizedPoints();

    std::vector<Line_2D_Indices> getLinesIndices(const int& shift = 0);
    std::vector<Line_3D> getLines();

    void move(double x, double y, double z);
    void move(Point_3D vector_3d);
    void teleport(double x, double y, double z);
    void teleport(Point_3D point_3d);
    void rotate(double x, double y, double z);
    void rotate(Point_3D angles);
};

//  box class
class Box : public Object_3D
{
protected:
    double width, height, depth;
protected:
    void setPoints();
    void setLines();
public:
    Box(double width, double height, double depth, Point_3D position = Point_3D(0, 0, 0), Point_3D rotation = Point_3D(0, 0, 0), bool ifLines = true);
};
