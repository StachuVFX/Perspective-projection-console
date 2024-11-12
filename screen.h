#pragma once

#include <iostream>
#include <vector>

#define PRINT(x) std::cout << x
#define LOG(x) std::cout << "LOG: " << x

#define PI 3.14159265359
#define RAD(x) x * PI / 180

#define WIDTH 80
#define HEIGHT 24

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

//  screen class
class Screen
{
private:
    //      Setup variables:
    // screen dimensions
    int m_width, m_height;
    // fov - field of view / view angle (in degrees), zV - view angle vertex depth (z-value)
    double fov, zV;
    // screen "pixels"
    char screen[HEIGHT][WIDTH];
public:
    Screen()
        : m_width(WIDTH), m_height(HEIGHT), fov(90), zV(-m_width)
    {
        LOG("zV: " << zV << "\n");
        Clear();
    }
    // my formula for zV found using a notebook, a pen, and the trigonometric table
    Screen(const int &width, const int &height, const double &fov)
        : m_width(width), m_height(height), fov(fov), zV(-width / tan(RAD(fov / 2)))
    {
        LOG("zV: " << zV << "\n");
        Clear();
    }

    //  clear the screen
    void Clear()
    {
        for (int i = 0; i < m_height; i++)
        {
            for (int j = 0; j < m_width; j++)
            {
                screen[i][j] = ' ';
            }
        }
    }

    //  fill the screen with a character
    void Fill(const char &character)
    {
        for (int i = 0; i < m_height; i++)
        {
            for (int j = 0; j < m_width; j++)
            {
                screen[i][j] = character;
            }
        }
    }

    //  draw a horizontal line
    void Draw(const Horizontal_Line& line, const char& character)
    {
        int y = m_height - ((int)line.y + m_height / 2) - 1;
        if (y > -1 && y < m_height)
        {
            for (int i = 0; i < m_width; i++)
            {
                screen[y][i] = character;
            }
        }
    }
    //  draw a horizontal line
    void Draw(const Vertical_Line& line, const char& character)
    {
        int x = (int)line.x + m_width / 2;
        if (x > -1 && x < m_width)
        {
            for (int i = 0; i < m_height; i++)
            {
                screen[i][x] = character;
            }
        }
    }
    //  draw normalized 2d points
    void Draw(const std::vector<Point_2D> &points_2d, const char &character)
    {
        for (int i = 0, x, y; i < points_2d.size(); i++)
        {
            x = (int)points_2d[i].x + m_width / 2;
            y = m_height - ((int)points_2d[i].y + m_height / 2) - 1;

            LOG("Point(" << points_2d[i].x << ", " << points_2d[i].y <<
                ") --> Round_Point(" << (int)points_2d[i].x << ", " << (int)points_2d[i].y <<
                ") --> Normalized_Point(" << x << ", " << y << ")");

            if (x > -1 && x < m_width && y > -1 && y < m_height)
            {
                screen[y][x] = character;
                PRINT("\n");
            }
            else
            {
                PRINT(" - Point out of bounds!\n");
            }
        }
    }
    //  project 3d points to 2d and draw them
    void Draw(const std::vector<Point_3D> &points_3d, const char &character)
    {
        std::vector<Point_2D> points_2d;
        Point_2D tmp_point_2d;
        for (int i = 0; i < points_3d.size(); i++)
        {
            // my projection formula derived from the slope-intercept line formula
            tmp_point_2d.x = (-zV * points_3d[i].x) / (points_3d[i].z - zV);
            tmp_point_2d.y = (-zV * points_3d[i].y) / (points_3d[i].z - zV);
            points_2d.push_back(tmp_point_2d);
        }
        Draw(points_2d, character);
    }

    //  display screen
    void Display()
    {
        PRINT(std::endl);
        for (int i = 0; i < m_height; i++)
        {
            for (int j = 0; j < m_width; j++)
            {
                PRINT(screen[i][j]);
            }
            PRINT(std::endl);
        }
    }
};
