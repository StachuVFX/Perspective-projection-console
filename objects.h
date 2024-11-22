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
    Horizontal_Line(double y = 0) : y(y) {}
};
//  vertical line class
class Vertical_Line
{
public:
    double x;
public:
    Vertical_Line(double x = 0) : x(x) {}
};

//  2D point class
class Point_2D
{
public:
    double x, y;
public:
    Point_2D(double x = 0, double y = 0) : x(x), y(y) {}
};
//  3D point class
class Point_3D
{
public:
    double x, y, z;
public:
    Point_3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    void move(double x, double y, double z)
    {
        this->x += x;
        this->y += y;
        this->z += z;
    }
    void move(Point_3D vector)
    {
        x += vector.x;
        y += vector.y;
        z += vector.z;
    }
};
//  2D line index class
class Line_2D_Indices {
public:
    int point_1, point_2;
public:
    Line_2D_Indices(int point_1 = 0, int point_2 = 0) : point_1(point_1), point_2(point_2) {}
};
//  2D line class
class Line_2D {
public:
    Point_2D point_1, point_2;
public:
    Line_2D(Point_2D point_1 = Point_2D(-1, -1), Point_2D point_2 = Point_2D(1, 1)) : point_1(point_1), point_2(point_2) {}
};
//  3D line class
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
    Point_3D rotation;
    bool ifLines;
    std::vector<Point_3D> points;
    std::vector<Line_2D_Indices> linesIndices;
public:
    Object_3D(std::vector<Point_3D> points = {}, Point_3D position = Point_3D(0, 0, 0), Point_3D rotation = Point_3D(0, 0, 0), std::vector<Line_2D_Indices> linesIndices = {}, bool ifLines = true)
        : points(points), position(position), rotation(rotation), linesIndices(linesIndices), ifLines(ifLines) {}

    Point_3D getPosition()
    {
        return position;
    }
    Point_3D getRotation()
    {
        return rotation;
    }

    std::vector<Point_3D> normalizedPoints()
    {
        std::vector<Point_3D> normPoints;
        Point_3D p0;
        double alpha = 0;
        Point_3D p1;
        double r;
        double beta = 0;
        double gamma;
        int p0p = 1;
        int p1p = 1;
        int multiplier = 1;
        for (int i = 0; i < points.size(); i++)
        {
            //  z axis rotation
            alpha = rotation.z;
            p0 = points[i];
            p1.z = p0.z;
            // step 1
            r = sqrt(pow(p0.x, 2) + pow(p0.y, 2));
            // step 2
            if (p0.x >= 0 && p0.y >= 0)
                p0p = 1;
            else if (p0.x < 0 && p0.y >= 0)
                p0p = 2;
            else if (p0.x < 0 && p0.y < 0)
                p0p = 3;
            else if (p0.x >= 0 && p0.y < 0)
                p0p = 4;
            // step 3
            beta = DEG(atan(abs(p0.y / p0.x)));
            beta = abs(beta + (p0p == 2 ? -180 : p0p == 3 ? 180 : p0p == 4 ? -360 : 0));
            // step 4
            gamma = alpha + beta;
            gamma -= floor(gamma / 360) * 360;
            // step 5 and 6
            p1.x = sqrt(pow(r, 2) / (pow(tan(RAD(gamma)), 2) + 1)) * SGN(cos(RAD(gamma)));
            p1.y = sqrt(pow(r, 2) / (pow(1 / tan(RAD(gamma)), 2) + 1)) * SGN(sin(RAD(gamma)));
            
            //  x axis rotation
            alpha = rotation.x;
            p0 = p1;
            // step 1
            r = sqrt(pow(p0.y, 2) + pow(p0.z, 2));
            // step 2
            if (p0.y >= 0 && p0.z >= 0)
                p0p = 1;
            else if (p0.y < 0 && p0.z >= 0)
                p0p = 2;
            else if (p0.y < 0 && p0.z < 0)
                p0p = 3;
            else if (p0.y >= 0 && p0.z < 0)
                p0p = 4;
            // step 3
            beta = DEG(atan(abs(p0.z / p0.y)));
            beta = abs(beta + (p0p == 2 ? -180 : p0p == 3 ? 180 : p0p == 4 ? -360 : 0));
            // step 4
            gamma = alpha + beta;
            gamma -= floor(gamma / 360) * 360;
            // step 5 and 6
            p1.y = sqrt(pow(r, 2) / (pow(tan(RAD(gamma)), 2) + 1)) * SGN(cos(RAD(gamma)));
            p1.z = sqrt(pow(r, 2) / (pow(1 / tan(RAD(gamma)), 2) + 1)) * SGN(sin(RAD(gamma)));

            //  y axis rotation
            alpha = rotation.y;
            p0 = p1;
            // step 1
            r = sqrt(pow(p0.z, 2) + pow(p0.x, 2));
            // step 2
            if (p0.z >= 0 && p0.x >= 0)
                p0p = 1;
            else if (p0.z < 0 && p0.x >= 0)
                p0p = 2;
            else if (p0.z < 0 && p0.x < 0)
                p0p = 3;
            else if (p0.z >= 0 && p0.x < 0)
                p0p = 4;
            // step 3
            beta = DEG(atan(abs(p0.x / p0.z)));
            beta = abs(beta + (p0p == 2 ? -180 : p0p == 3 ? 180 : p0p == 4 ? -360 : 0));
            // step 4
            gamma = alpha + beta;
            gamma -= floor(gamma / 360) * 360;
            // step 5 and 6
            p1.z = sqrt(pow(r, 2) / (pow(tan(RAD(gamma)), 2) + 1)) * SGN(cos(RAD(gamma)));
            p1.x = sqrt(pow(r, 2) / (pow(1 / tan(RAD(gamma)), 2) + 1)) * SGN(sin(RAD(gamma)));

            p1.move(position);
            normPoints.push_back(p1);
        }
        return normPoints;
    }

    std::vector<Line_2D_Indices> getLinesIndices(const int &shift = 0)
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
    void rotate(double x, double y, double z)
    {
        rotation.x += x;
        rotation.y += y;
        rotation.z += z;
    }
    void rotate(Point_3D angles)
    {
        rotation.x += angles.x;
        rotation.y += angles.y;
        rotation.z += angles.z;
    }
};

//  box class
class Box : public Object_3D
{
protected:
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
    Box(double width, double height, double depth, Point_3D position = Point_3D(0, 0, 0), Point_3D rotation = Point_3D(0, 0, 0), bool ifLines = true)
        : width(width), height(height), depth(depth)
    {
        this->position = position;
        this->rotation = rotation;
        this->ifLines = ifLines;
        setPoints();
        if (ifLines) setLines();
    }
};
