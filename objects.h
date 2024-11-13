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
//  2D line index struct
struct Line_2D_Indices {
public:
    int point_1, point_2;
public:
    Line_2D_Indices() : point_1(0), point_2(0) {}
    Line_2D_Indices(int point_1, int point_2) : point_1(point_1), point_2(point_2) {}
};
//  2D line struct
struct Line_2D {
public:
    Point_2D point_1, point_2;
public:
    Line_2D() : point_1(Point_2D(-1, -1)), point_2(Point_2D(1, 1)) {}
    Line_2D(Point_2D point_1, Point_2D point_2) : point_1(point_1), point_2(point_2) {}
};
//  3D line struct
struct Line_3D {
public:
    Point_3D point_1, point_2;
public:
    Line_3D() : point_1(Point_3D(-1, -1, -1)), point_2(Point_3D(1, 1, 1)) {}
    Line_3D(Point_3D point_1, Point_3D point_2) : point_1(point_1), point_2(point_2) {}
};

//  3D object class
class Object_3D : Point_3D
{
protected:
    double x, y, z;
    std::vector<Point_3D> points;
    std::vector<Line_2D_Indices> linesIndices;
public:
    Object_3D() : x(0), y(0), z(0) {}
    Object_3D(double x, double y, double z) : x(x), y(y), z(z) {}
    Object_3D(std::vector<Point_3D> points) : x(0), y(0), z(0), points(points) {}
    Object_3D(std::vector<Point_3D> points, std::vector<Line_2D_Indices> linesIndices) : x(0), y(0), z(0), points(points), linesIndices(linesIndices) {}
    Object_3D(double x, double y, double z, std::vector<Point_3D> points) : x(x), y(y), z(z), points(points) {}
    Object_3D(double x, double y, double z, std::vector<Point_3D> points, std::vector<Line_2D_Indices> linesIndices) : x(x), y(y), z(z), points(points), linesIndices(linesIndices) {}

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

    std::vector<Line_2D_Indices> getLinesIndices()
    {
        return linesIndices;
    }
    std::vector<Line_2D_Indices> getLinesIndices(const int shift)
    {
        std::vector<Line_2D_Indices> shiftedLinesIndices;
        for (int i = 0; i < linesIndices.size(); i++)
        {
            shiftedLinesIndices.push_back({ linesIndices[i].point_1 + shift, linesIndices[i].point_2 + shift });
        }
        return shiftedLinesIndices;
    }
    std::vector<Line_3D> getLines()
    {
        std::vector<Line_3D> lines;
        for (int i = 0; i < linesIndices.size(); i++)
        {
            lines.push_back(Line_3D(points[linesIndices[i].point_1], points[linesIndices[i].point_2]));
        }
        return lines;
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
class Box : Point_3D
{
private:
    double x, y, z;
    double width, height, depth;
    bool ifLines;
    std::vector<Point_3D> points;
    std::vector<Line_2D_Indices> linesIndices;
private:
    void setPoints()
    {
        points.push_back(Point_3D(-width / 2, -height / 2, -depth / 2));
        points.push_back(Point_3D( width / 2, -height / 2, -depth / 2));
        points.push_back(Point_3D( width / 2,  height / 2, -depth / 2));
        points.push_back(Point_3D(-width / 2,  height / 2, -depth / 2));
        points.push_back(Point_3D(-width / 2, -height / 2,  depth / 2));
        points.push_back(Point_3D( width / 2, -height / 2,  depth / 2));
        points.push_back(Point_3D( width / 2,  height / 2,  depth / 2));
        points.push_back(Point_3D(-width / 2,  height / 2,  depth / 2));
    }
    void setLines()
    {
        linesIndices.push_back({ 0, 1 });
        linesIndices.push_back({ 1, 2 });
        linesIndices.push_back({ 2, 3 });
        linesIndices.push_back({ 3, 0 });

        linesIndices.push_back({ 4, 5 });
        linesIndices.push_back({ 5, 6 });
        linesIndices.push_back({ 6, 7 });
        linesIndices.push_back({ 7, 4 });

        linesIndices.push_back({ 0, 4 });
        linesIndices.push_back({ 1, 5 });
        linesIndices.push_back({ 2, 6 });
        linesIndices.push_back({ 3, 7 });
    }
public:
    Box(bool ifLines = false) : x(0), y(0), z(0), width(2), height(2), depth(2), ifLines(ifLines)
    {
        setPoints();
        if (ifLines) setLines();
    }
    Box(double width, double height, double depth, double x = 0, double y = 0, double z = 0, bool ifLines = false)
        : x(x), y(y), z(z), width(width), height(height), depth(depth), ifLines(ifLines)
    {
        setPoints();
        if (ifLines) setLines();
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

    std::vector<Line_2D_Indices> getLinesIndices()
    {
        return linesIndices;
    }
    std::vector<Line_2D_Indices> getLinesIndices(const int shift)
    {
        std::vector<Line_2D_Indices> shiftedLinesIndices;
        for (int i = 0; i < linesIndices.size(); i++)
        {
            shiftedLinesIndices.push_back({ linesIndices[i].point_1 + shift, linesIndices[i].point_2 + shift });
        }
        return shiftedLinesIndices;
    }
    std::vector<Line_3D> getLines()
    {
        std::vector<Line_3D> lines;
        for (int i = 0; i < linesIndices.size(); i++)
        {
            lines.push_back(Line_3D(points[linesIndices[i].point_1], points[linesIndices[i].point_2]));
        }
        return lines;
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
