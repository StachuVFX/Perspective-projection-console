#pragma once

#include <iostream>
#include <string>

#include "objects.h"

#define PRINT(x) std::cout << x
#define LOG(x) std::cout << "LOG: " << x

#define PI 3.14159265359
#define RAD(x) x * PI / 180

#define ONE_IF_ZERO(x) ((x == 0) ? 1 : x)

#define WIDTH 120
#define HEIGHT 30
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
public:
    Screen()
        : m_width(WIDTH), m_height(HEIGHT), fov(90), zV(-m_width / 2)
    {
        LOG("zV: " << zV << "\n");
        clear();
    }
    // my formula for zV found using a notebook, a pen, and the trigonometric table
    Screen(const int &width, const int &height, const double &fov)
        : m_width(width), m_height(height), fov(fov), zV(-(width / 2) / tan(RAD(fov / 2)))
    {
        LOG("zV: " << zV << "\n");
        clear();
    }

    //  clear the screen
    void clear()
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
    void fill(const char &character)
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
    void draw(const Horizontal_Line& line, const char& character)
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
    void draw(const Vertical_Line& line, const char& character)
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
    //  draw lines, each between 2 points
    void draw(const std::vector<Line_2D>& lines_2d, const char& character)
    {
        double lineWidth, lineHeight, lineLength;
        double x, y;
        Point_2D tmp_point_2d;
        std::vector<Point_2D> points_2d;
        for (int i = 0; i < lines_2d.size(); i++)
        {
            lineWidth = lines_2d[i].point_1.x - lines_2d[i].point_2.x;
            lineHeight = lines_2d[i].point_1.y - lines_2d[i].point_2.y;
            lineLength = abs(lineWidth) > abs(lineHeight) ? abs(lineWidth) : abs(lineHeight);
            for (int j = 0; j < lineLength; j++)
            {
                //x = lines_2d[i].point_1.x - (lineWidth / (abs(lineWidth) - j + 1));
                //y = lines_2d[i].point_1.y - (lineHeight / (abs(lineHeight) - j + 1));
                x = lines_2d[i].point_1.x - j * lineWidth / ONE_IF_ZERO(lineLength);    // here!
                y = lines_2d[i].point_1.y - j * lineHeight / ONE_IF_ZERO(lineLength);
                tmp_point_2d = Point_2D(x, y);
                points_2d.push_back(tmp_point_2d);
            }
        }
        draw(points_2d, character);
    }
    //  draw normalized 2d points
    void draw(const std::vector<Point_2D> &points_2d, const char &character)
    {
        for (int i = 0, x, y; i < points_2d.size(); i++)
        {
            x = (int)points_2d[i].x + m_width / 2;
            y = m_height - ((int)points_2d[i].y + m_height / 2) - 1;

            // out of bound check then draw
            if (x > -1 && x < m_width && y > -1 && y < m_height)
            {
                screen[y][x] = character;
            }
        }
    }
    //  project 3d points to 2d and draw them (without lines)
    void draw(const std::vector<Point_3D> &points_3d, const char &character)
    {
        Point_2D tmp_point_2d;
        std::vector<Point_2D> points_2d;
        for (int i = 0; i < points_3d.size(); i++)
        {
            // my projection formula derived from the slope-intercept line formula
            tmp_point_2d.x = (-zV * points_3d[i].x) / (points_3d[i].z - zV);
            tmp_point_2d.y = (-zV * points_3d[i].y) / (points_3d[i].z - zV);
            points_2d.push_back(tmp_point_2d);
        }
        draw(points_2d, character);
    }
    //  project 3d points to 2d and draw them (with lines)
    void draw(const std::vector<Point_3D> &points_3d, const char &character, const std::vector<Line_2D_Indices> &linesIndices, const char &linesCharacter = '.')
    {
        Point_2D tmp_point_2d;
        std::vector<Point_2D> points_2d;
        std::vector<Line_2D> lines_2d;
        for (int i = 0; i < points_3d.size(); i++)
        {
            // my projection formula derived from the slope-intercept line formula
            tmp_point_2d.x = (-zV * points_3d[i].x) / (points_3d[i].z - zV);
            tmp_point_2d.y = (-zV * points_3d[i].y) / (points_3d[i].z - zV);
            points_2d.push_back(tmp_point_2d);
        }

        // creating lines from indices
        for (int i = 0; i < linesIndices.size(); i++)
        {
            lines_2d.push_back(Line_2D(points_2d[linesIndices[i].point_1], points_2d[linesIndices[i].point_2]));
        }
        
        draw(lines_2d, linesCharacter);
        draw(points_2d, character);
    }
    //  draw all points of objects vector
    void draw(std::vector<Object_3D>& objects_3d, const char& character)
    {
        std::vector<Point_3D> all_points_3d;
        std::vector<Line_2D_Indices> all_linesIndices;
        std::vector<Point_3D> tmp_points_3d;
        std::vector<Line_2D_Indices> tmp_linesIndices;
        for (int i = 0; i < objects_3d.size(); i++)
        {
            tmp_points_3d = objects_3d[i].normalizedPoints();
            tmp_linesIndices = objects_3d[i].getLinesIndices(all_points_3d.size());
            for (int j = 0; j < tmp_linesIndices.size(); j++)
            {
                all_linesIndices.push_back(tmp_linesIndices[j]);
            }
            for (int j = 0; j < tmp_points_3d.size(); j++)
            {
                all_points_3d.push_back(tmp_points_3d[j]);
            }
        }
        draw(all_points_3d, character, all_linesIndices);
    }
    //  draw all points of box vector
    void draw(std::vector<Box>& objects_3d, const char& character)
    {
        std::vector<Point_3D> all_points_3d;
        std::vector<Line_2D_Indices> all_linesIndices;
        std::vector<Point_3D> tmp_points_3d;
        std::vector<Line_2D_Indices> tmp_linesIndices;
        for (int i = 0; i < objects_3d.size(); i++)
        {
            tmp_points_3d = objects_3d[i].normalizedPoints();
            tmp_linesIndices = objects_3d[i].getLinesIndices(all_points_3d.size());
            for (int j = 0; j < tmp_linesIndices.size(); j++)
            {
                all_linesIndices.push_back(tmp_linesIndices[j]);
            }
            for (int j = 0; j < tmp_points_3d.size(); j++)
            {
                all_points_3d.push_back(tmp_points_3d[j]);
            }
        }
        draw(all_points_3d, character, all_linesIndices);
    }

    //  display screen line by line as  strings
    void display()
    {
        /*PRINT(std::endl);
        for (int i = 0; i < m_height; i++)
        {
            char line[WIDTH + 1];
            line[m_width] = '\0';
            for (int j = 0; j < m_width; j++)
            {
                line[j] = screen[i][j];
            }
            PRINT(line << std::endl);
        }*/

        char screenText[HEIGHT * (WIDTH + 1)];
        for (int i = 0; i < m_height - 1; i++)
        {
            screenText[i * (m_width + 1) + m_width] = '\n';
        }
        screenText[m_height * (m_width + 1) - 1] = '\0';
        for (int i = 0; i < m_height; i++)
        {
            for (int j = 0; j < m_width; j++)
            {
                screenText[i * (m_width + 1) + j] = screen[i][j];
            }
        }
        PRINT(std::endl << screenText);
    }
};
