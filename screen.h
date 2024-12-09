#pragma once

#include <iostream>

#include "objects.h"

#define PRINT(x) std::cout << x
#define LOG(x) std::cout << std::endl << "LOG: " << x

#define ONE_IF_ZERO(x) ((x == 0) ? 1 : x)

//#define WIDTH 120
//#define HEIGHT 30
#define DEBUG_TEXT_LINES 2
#define WIDTH 156
#define HEIGHT 39
#define FOV 90

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
    // objects vector
    std::vector<Object_3D> m_objects;
public:
    // should the screen keep being displayed
    bool isRunning = true;
    // characters to print points and lines with
    char m_pointsChar = 'o', m_linesChar = '.';
public:
    Screen();
    Screen(const int& width, const int& height, const double& fov);

    //  add objects
    void add_objects(std::vector<Object_3D>& objects);

    // move all objects
    void move_objects(double x, double y, double z);
    // rotate all objects
    void rotate_objects(double x, double y, double z);

    // listen to keypresses
    void keyboard_events();

    //  clear the screen
    void clear();
    //  fill the screen with a character
    void fill(const char& character);

    //  draw a horizontal line
    void draw_line_horizontal(const Horizontal_Line& line, const char& character);
    //  draw a horizontal line
    void draw_line_vertical(const Vertical_Line& line, const char& character);

    //  draw 2d lines, each between 2 points
    void draw_lines_2d(const std::vector<Line_2D>& lines_2d);
    //  draw 3d lines, each between 2 points
    void draw_lines_3d(const std::vector<Line_3D>& lines_3d);
    //  draw normalized 2d points (with console character width correction)
    void draw_points_2d(const std::vector<Point_2D>& points_2d, const char& character);
    //  project 3d points to 2d and draw them (without lines, cutting negative z)
    void draw_points_3d(const std::vector<Point_3D>& points_3d, char linesChar);
    //  draw all objects (cutting negative z)
    void draw();

    //  display screen
    void display();
};
