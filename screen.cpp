#include <string>
#include <conio.h>

#include "screen.h"

//  screen class
Screen::Screen()
    : m_width(WIDTH), m_height(HEIGHT), fov(90), zV(-m_width / 2)
{
    LOG("zV: " << zV << "\n");
    clear();
}
// my formula for zV found using a notebook, a pen, and the trigonometric table
Screen::Screen(const int& width, const int& height, const double& fov)
    : m_width(width), m_height(height), fov(fov), zV(-(width / 2) / tan(RAD(fov / 2)))
{
    LOG("zV: " << zV << "\n");
    clear();
}

//  add objects
void Screen::add_objects(std::vector<Object_3D>& objects)
{
    for (int i = 0; i < objects.size(); i++)
    {
        m_objects.push_back(objects[i]);
    }
}

// move all objects
void Screen::move_objects(double x, double y, double z)
{
    for (int i = 0; i < m_objects.size(); i++)
    {
        m_objects[i].move(x, y, z);
    }
}
// rotate all objects
void Screen::rotate_objects(double x, double y, double z)
{
    for (int i = 0; i < m_objects.size(); i++)
    {
        m_objects[i].rotate(x, y, z);
    }
}

// listen to keypresses
void Screen::keyboard_events()
{
    char key = ' ';
    char specialKey = ' ';
    do
    {
        key = _getch();
        switch (key)
        {
        case 27:    // SPACE
            PRINT("\nESC pressed, stopping the program...\n");
            isRunning = false;
            break;
        case 13:    // ENTER
            break;
        case -32:   // special keys
            specialKey = _getch();
            switch (specialKey)
            {
            case 72:    // Up Arrow
                move_objects(0, 1, 0);
                break;
            case 80:    // Down Arrow
                move_objects(0, -1, 0);
                break;
            case 75:    // Left Arrow
                move_objects(-1, 0, 0);
                break;
            case 77:    // Right Arrow
                move_objects(1, 0, 0);
                break;
            default:
                //LOG("Key: " << (int)key << " -> " << (int)specialKey << std::endl);
                break;
            }
            break;
        case 'p':    // P (depth up)
            move_objects(0, 0, 1);
            break;
        case 'l':    // L (depth down)
            move_objects(0, 0, -1);
            break;
        case 'i':    // I (rotation x up)
            rotate_objects(-2.5, 0, 0);
            break;
        case 'o':    // O (rotation x down)
            rotate_objects(2.5, 0, 0);
            break;
        case 'j':    // J (rotation y up)
            rotate_objects(0, -2.5, 0);
            break;
        case 'k':    // K (rotation y down)
            rotate_objects(0, 2.5, 0);
            break;
        case 'n':    // N (rotation z up)
            rotate_objects(0, 0, -2.5);
            break;
        case 'm':    // M (rotation z down)
            rotate_objects(0, 0, 2.5);
            break;
        default:
            //LOG("Key: " << (int)key);
            break;
        }
    } while (isRunning && false);
}

//  clear the screen
void Screen::clear()
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
void Screen::fill(const char& character)
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
void Screen::draw_line_horizontal(const Horizontal_Line& line, const char& character)
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
void Screen::draw_line_vertical(const Vertical_Line& line, const char& character)
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

//  draw 2d lines, each between 2 points
void Screen::draw_lines_2d(const std::vector<Line_2D>& lines_2d)
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
            x = lines_2d[i].point_1.x - j * lineWidth / ONE_IF_ZERO(lineLength);
            y = lines_2d[i].point_1.y - j * lineHeight / ONE_IF_ZERO(lineLength);
            tmp_point_2d = Point_2D(x, y);
            points_2d.push_back(tmp_point_2d);
        }
    }
    draw_points_2d(points_2d, m_linesChar);
}
//  draw 3d lines, each between 2 points
void Screen::draw_lines_3d(const std::vector<Line_3D>& lines_3d)
{
    double lineWidth, lineHeight, lineDepth, lineLength;
    double x, y, z;
    Point_3D tmp_point_3d;
    std::vector<Point_3D> points_3d;
    for (int i = 0; i < lines_3d.size(); i++)
    {
        lineWidth = lines_3d[i].point_1.x - lines_3d[i].point_2.x;
        lineHeight = lines_3d[i].point_1.y - lines_3d[i].point_2.y;
        lineDepth = lines_3d[i].point_1.z - lines_3d[i].point_2.z;
        lineLength = abs(lineWidth) > abs(lineHeight) && abs(lineWidth) > abs(lineDepth) ? abs(lineWidth) : abs(lineHeight) > abs(lineDepth) ? abs(lineHeight) : abs(lineDepth);
        for (int j = 0; j < lineLength; j++)
        {
            x = lines_3d[i].point_1.x - j * lineWidth / ONE_IF_ZERO(lineLength);
            y = lines_3d[i].point_1.y - j * lineHeight / ONE_IF_ZERO(lineLength);
            z = lines_3d[i].point_1.z - j * lineDepth / ONE_IF_ZERO(lineLength);
            tmp_point_3d = Point_3D(x, y, z);
            points_3d.push_back(tmp_point_3d);
        }
    }
    draw_points_3d(points_3d, m_linesChar);
}
//  draw normalized 2d points (with console character width correction)
void Screen::draw_points_2d(const std::vector<Point_2D>& points_2d, const char& character)
{
    for (int i = 0, x, y; i < points_2d.size(); i++)
    {
        x = (int)(points_2d[i].x * 2) + m_width / 2;
        y = m_height - ((int)points_2d[i].y + m_height / 2) - 1;

        // out of bound check then draw
        if (x > -1 && x < m_width && y > -1 && y < m_height)
        {
            screen[y][x] = character;
        }
    }
}
//  project 3d points to 2d and draw them (without lines, cutting negative z)
void Screen::draw_points_3d(const std::vector<Point_3D>& points_3d, char pointsChar)
{
    Point_2D tmp_point_2d;
    std::vector<Point_2D> points_2d;
    for (int i = 0; i < points_3d.size(); i++)
    {
        if (points_3d[i].z > 0)
        {
            // my projection formula derived from the slope-intercept line formula
            tmp_point_2d.x = (-zV * points_3d[i].x) / (points_3d[i].z - zV);
            tmp_point_2d.y = (-zV * points_3d[i].y) / (points_3d[i].z - zV);
            points_2d.push_back(tmp_point_2d);
        }
    }
    draw_points_2d(points_2d, pointsChar);
}
//  draw all objects (cutting negative z)
void Screen::draw()
{
    std::vector<Point_3D> all_points_3d;
    std::vector<Line_2D_Indices> all_linesIndices;
    std::vector<Line_3D> all_lines_3d;
    std::vector<Point_3D> tmp_points_3d;
    std::vector<Line_2D_Indices> tmp_linesIndices;
    for (int i = 0; i < m_objects.size(); i++)
    {
        tmp_points_3d = m_objects[i].normalizedPoints();
        tmp_linesIndices = m_objects[i].getLinesIndices(all_points_3d.size());
        for (int j = 0; j < tmp_linesIndices.size(); j++)
        {
            all_linesIndices.push_back(tmp_linesIndices[j]);
        }
        for (int j = 0; j < tmp_points_3d.size(); j++)
        {
            all_points_3d.push_back(tmp_points_3d[j]);
        }
    }

    // creating lines from indices
    for (int i = 0; i < all_linesIndices.size(); i++)
    {
        all_lines_3d.push_back(Line_3D(all_points_3d[all_linesIndices[i].point_1], all_points_3d[all_linesIndices[i].point_2]));
    }

    draw_lines_3d(all_lines_3d);
    draw_points_3d(all_points_3d, m_pointsChar);
}

//  display screen
void Screen::display()
{
    // first display position and rotation
    printf("\n\nPosition: %g, %g, %g\nRotation: %g, %g, %g", m_objects[0].getPosition().x, m_objects[0].getPosition().y, m_objects[0].getPosition().z, m_objects[0].getRotation().x, m_objects[0].getRotation().y, m_objects[0].getRotation().z);
    // then display the screen as a single string
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
    //PRINT("\n\n" << screenText);
    PRINT("\n" << screenText);
}
