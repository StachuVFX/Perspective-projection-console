#pragma once

#include <vector>

//  horizontal line struct
class Horizontal_Line
{
public:
    double y;
public:
    Horizontal_Line(double y = 0) : y(y) {}
};
//  vertical line struct
class Vertical_Line
{
public:
    double x;
public:
    Vertical_Line(double x = 0) : x(x) {}
};

//  2D point struct
class Point_2D
{
public:
    double x, y;
public:
    Point_2D(double x = 0, double y = 0) : x(x), y(y) {}
};
//  3D point struct
class Point_3D
{
public:
    double x, y, z;
public:
    Point_3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
};
//  2D line index struct
class Line_2D_Indices {
public:
    int point_1, point_2;
public:
    Line_2D_Indices(int point_1 = 0, int point_2 = 0) : point_1(point_1), point_2(point_2) {}
};
//  2D line struct
class Line_2D {
public:
    Point_2D point_1, point_2;
public:
    Line_2D(Point_2D point_1 = Point_2D(-1, -1), Point_2D point_2 = Point_2D(1, 1)) : point_1(point_1), point_2(point_2) {}
};
//  3D line struct
class Line_3D {
public:
    Point_3D point_1, point_2;
public:
    Line_3D(Point_3D point_1 = Point_3D(-1, -1, -1), Point_3D point_2 = Point_3D(1, 1, 1)) : point_1(point_1), point_2(point_2) {}
};

//  3D object class
class Object_3D
{
protected:
    Point_3D position;
    //double width, height, depth;
    bool ifLines;
    std::vector<Point_3D> points;
    std::vector<Line_2D_Indices> linesIndices;
public:
    /*Object_3D(bool ifLines = true) : x(0), y(0), z(0), ifLines(ifLines) {}
    Object_3D(double x, double y, double z, bool ifLines = true) : x(x), y(y), z(z), ifLines(ifLines) {}
    Object_3D(std::vector<Point_3D> points, bool ifLines = true) : x(0), y(0), z(0), points(points), ifLines(ifLines) {}
    Object_3D(std::vector<Point_3D> points, std::vector<Line_2D_Indices> linesIndices = {}, bool ifLines = true) : x(0), y(0), z(0), points(points), linesIndices(linesIndices), ifLines(ifLines) {}
    Object_3D(double x, double y, double z, std::vector<Point_3D> points, bool ifLines = true) : x(x), y(y), z(z), points(points), ifLines(ifLines) {}*/
    Object_3D(Point_3D position = Point_3D(0, 0, 0), std::vector<Point_3D> points = {}, std::vector<Line_2D_Indices> linesIndices = {}, bool ifLines = true) : position(position), points(points), linesIndices(linesIndices), ifLines(ifLines) {}

    Point_3D getPosition()
    {
        return position;
    }

    std::vector<Point_3D> normalizedPoints()
    {
        std::vector<Point_3D> normPoints;
        for (int i = 0; i < points.size(); i++)
        {
            normPoints.push_back(Point_3D(points[i].x + position.x, points[i].y + position.y, points[i].z + position.z));
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
        position.x += x;
        position.y += y;
        position.z += z;
    }
    void move(Point_3D vector_3d)
    {
        position.x += vector_3d.x;
        position.y += vector_3d.y;
        position.z += vector_3d.z;
    }
    void teleport(double x, double y, double z)
    {
        position.x = x;
        position.y = y;
        position.z = z;
    }
    void teleport(Point_3D point_3d)
    {
        position.x = point_3d.x;
        position.y = point_3d.y;
        position.z = point_3d.z;
    }
};

//  box class
class Box : public Object_3D
{
protected:
    //double x, y, z;
    //bool ifLines;
    //std::vector<Point_3D> points;
    //std::vector<Line_2D_Indices> linesIndices;
    double width, height, depth;
protected:
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
    /*Box(double width = 2, double height = 2, double depth = 2, double x = 0, double y = 0, double z = 0, bool ifLines = true)
        : x(x), y(y), z(z), width(width), height(height), depth(depth), ifLines(ifLines)
    {
        setPoints();
        if (ifLines) setLines();
    }*/
    Box(double width = 2, double height = 2, double depth = 2, Point_3D position = Point_3D(0, 0, 0), bool ifLines = true) : width(width), height(height), depth(depth)
    {
        this->position = position;
        this->ifLines = ifLines;
        setPoints();
        if (ifLines) setLines();
    }
    
    /*std::vector<Point_3D> normalizedPoints()
    {
        std::vector<Point_3D> normPoints;
        for (int i = 0; i < points.size(); i++)
        {
            normPoints.push_back(Point_3D(points[i].x + x, points[i].y + y, points[i].z + z));
        }
        return normPoints;
    }*/

    /*std::vector<Line_2D_Indices> getLinesIndices()
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
    }*/

    /*void move(double x, double y, double z)
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
    }*/
};
