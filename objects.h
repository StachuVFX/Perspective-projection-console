#pragma once

#include <vector>

//  horizontal line struct
struct Horizontal_Line
{
public:
    double y;
public:
    Horizontal_Line() : y(0) {}
    Horizontal_Line(double y) : y(y) {}
};
//  vertical line struct
struct Vertical_Line
{
public:
    double x;
public:
    Vertical_Line() : x(0) {}
    Vertical_Line(double x) : x(x) {}
};

//  2D point struct
struct Point_2D
{
public:
    double x, y;
public:
    Point_2D() : x(0), y(0) {}
    Point_2D(double x, double y) : x(x), y(y) {}
};
//  3D point struct
struct Point_3D
{
public:
    double x, y, z;
public:
    Point_3D() : x(0), y(0), z(0) {}
    Point_3D(double x, double y, double z) : x(x), y(y), z(z) {}
};

//  3D object class
class Object : Point_3D
{
protected:
    double x, y, z;
    std::vector<Point_3D> points;
public:
    Object() : x(0), y(0), z(0) {}
    Object(double x, double y, double z) : x(x), y(y), z(z) {}
    Object(std::vector<Point_3D> points) : x(0), y(0), z(0), points(points) {}
    Object(double x, double y, double z, std::vector<Point_3D> points) : x(x), y(y), z(z), points(points) {}

    Point_3D getPosition()
    {
        return Point_3D(x, y, z);
    }

    std::vector<Point_3D> normalizedPoints()
    {
        std::vector<Point_3D> normPoints;
        for (int i = 0; i < points.size(); i++)
        {
            normPoints.push_back(Point_3D(points[i].x + x, points[i].y + y, points[i].z + z));
        }
        return normPoints;
    }

    void move(double x, double y, double z)
    {
        this->x += x;
        this->y += y;
        this->z += z;
    }
    void move(Point_3D vector_3d)
    {
        x += vector_3d.x;
        y += vector_3d.y;
        z += vector_3d.z;
    }
    void teleport(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    void teleport(Point_3D vector_3d)
    {
        x = vector_3d.x;
        y = vector_3d.y;
        z = vector_3d.z;
    }
};

//  box class
class Box : Object, Point_3D
{
private:
    double x, y, z;
    double width, height, depth;
    std::vector<Point_3D> points;
private:
    void setPoints()
    {
        points.push_back(Point_3D(-width / 2, -height / 2, -depth / 2));
        points.push_back(Point_3D(-width / 2, -height / 2,  depth / 2));
        points.push_back(Point_3D(-width / 2,  height / 2, -depth / 2));
        points.push_back(Point_3D(-width / 2,  height / 2,  depth / 2));
        points.push_back(Point_3D( width / 2, -height / 2, -depth / 2));
        points.push_back(Point_3D( width / 2, -height / 2,  depth / 2));
        points.push_back(Point_3D( width / 2,  height / 2, -depth / 2));
        points.push_back(Point_3D( width / 2,  height / 2,  depth / 2));
    }
public:
    Box() : x(0), y(0), z(0), width(2), height(2), depth(2) {}
    Box(double width, double height, double depth)
        : x(0), y(0), z(0), width(width), height(height), depth(depth)
    {
        setPoints();
    }
    Box(double x, double y, double z, double width, double height, double depth)
        : x(x), y(y), z(z), width(width), height(height), depth(depth)
    {
        setPoints();
    }
    
    std::vector<Point_3D> normalizedPoints()
    {
        std::vector<Point_3D> normPoints;
        for (int i = 0; i < points.size(); i++)
        {
            normPoints.push_back(Point_3D(points[i].x + x, points[i].y + y, points[i].z + z));
        }
        return normPoints;
    }
};
