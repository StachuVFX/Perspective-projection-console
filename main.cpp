#include <Windows.h>

#include "screen.h"

#define INTERVAL 10

int main()
{
    PRINT("My shot at perspective projection of 3D points to a 2D screen\n\n");

    //  TODO:
    // - move methods from .h to .cpp files (done)
    // - not displaying negative z
    // - read objects from a file
    // - make proper rotation using vectors
    // - absolute coordinates to camera coordinates
    // - threads?

    //      Setup:
    // X and Y axes
    Horizontal_Line hLine(0);
    Vertical_Line vLine(0);

    // objects
    //std::vector<Point_3D> square = {
    //    /*Point_3D( 8, 8, 0),
    //    Point_3D(-8, 8, 0),
    //    Point_3D(-8,-8, 0),
    //    Point_3D( 8,-8, 0)*/
    //    Point_3D( 12, 0, 0),
    //    Point_3D( 0, 12, 0),
    //    Point_3D(-12, 0, 0),
    //    Point_3D( 0,-12, 0)
    //};
    //Point_3D square_position(0, 0, 20);
    //Point_3D square_rotation(0, 0, 0);
    //std::vector<Line_2D_Indices> square_linesIndices = {
    //    Line_2D_Indices(0, 1),
    //    Line_2D_Indices(1, 2),
    //    Line_2D_Indices(2, 3),
    //    Line_2D_Indices(3, 0)
    //};
    //bool square_ifLines = true;

    std::vector<Point_3D> pyramid = {
        Point_3D(-16,-16,-16),
        Point_3D( 16,-16,-16),
        Point_3D( 16,-16, 16),
        Point_3D(-16,-16, 16),
        Point_3D( 0, 16, 0)
    };
    Point_3D pyramid_position(0, 0, 32);
    Point_3D pyramid_rotation(0, 0, 0);
    std::vector<Line_2D_Indices> pyramid_linesIndices = {
        Line_2D_Indices(0, 1),
        Line_2D_Indices(1, 2),
        Line_2D_Indices(2, 3),
        Line_2D_Indices(3, 0),
        Line_2D_Indices(0, 4),
        Line_2D_Indices(1, 4),
        Line_2D_Indices(2, 4),
        Line_2D_Indices(3, 4)
    };
    bool pyramid_ifLines = true;

    /*std::vector<Point_3D> triangle = {
        Point_3D(-16,-16,-16),
        Point_3D( 16,-16,-16),
        Point_3D( 16,-16, 16),
        Point_3D(-16,-16, 16),
        Point_3D( 0, 16, 0)
    };
    Point_3D triangle_position(0, 0, 32);
    Point_3D triangle_rotation(0, 0, 0);
    std::vector<Line_2D_Indices> triangle_linesIndices = {
        Line_2D_Indices(0, 1),
        Line_2D_Indices(1, 2),
        Line_2D_Indices(2, 3),
        Line_2D_Indices(3, 0),
        Line_2D_Indices(0, 4),
        Line_2D_Indices(1, 4),
        Line_2D_Indices(2, 4),
        Line_2D_Indices(3, 4)
    };
    bool triangle_ifLines = true;*/

    std::vector<Object_3D> objectVector = {
        //Object_3D(square, square_position, square_rotation, square_linesIndices, square_ifLines),
        //Box( 16, 16, 16, Point_3D(20, 0, 40), Point_3D(0, 0, 0), true)
        Object_3D(pyramid, pyramid_position, pyramid_rotation, pyramid_linesIndices, pyramid_ifLines)
        //Object_3D(triangle, triangle_position, triangle_rotation, triangle_linesIndices, triangle_ifLines)
        // boxes (width, height, depth, position, rotation, ifLines?)
        //Box( 8,  8, 8, Point_3D(-24, -10, 10), Point_3D(0, 0, 125), false),
        //Box(16, 16, 16, Point_3D(  0,   0, 20), Point_3D(0, 0, 35), false)
        //Box(10,  5, 10, Point_3D( 36, -10, 10)),
        //Box(10,  5, 10, Point_3D( 36,  10, 10)),
        //Box(10,  5, 10, Point_3D(-36,  10, 10))
    };

    // lines (for debugging)
    //std::vector<Line_2D> lineVector = {
    //    //Line_2D(Point_2D(-20, -10), Point_2D( 20, -10)),
    //    //Line_2D(Point_2D( 20, -10), Point_2D( 20,  10)),
    //    //Line_2D(Point_2D( 20,  10), Point_2D(-20,  10)),
    //    //Line_2D(Point_2D(-20,  10), Point_2D(-20, -10))
    //    Line_2D(Point_2D(  0, -10), Point_2D( 20,   0)),
    //    Line_2D(Point_2D( 20,   0), Point_2D(  0,  10)),
    //    Line_2D(Point_2D(  0,  10), Point_2D(-20,   0)),
    //    Line_2D(Point_2D(-20,   0), Point_2D(  0, -10))
    //};

    //      Drawing:
    // screen
    Screen screen(WIDTH, HEIGHT, FOV);

    // add objects
    screen.add_objects(objectVector);
    
    // game loop
    while (screen.isRunning)
    {
        // clear the screen
        screen.clear();

        // draw lines
        screen.draw_line_horizontal(hLine, '-');
        screen.draw_line_vertical(vLine, '|');

        // draw objects
        screen.draw();

        // debug lines
        //screen.draw_lines(lineVector);

        // display
        Sleep(INTERVAL);
        screen.display();

        // keyboard events
        screen.keyboard_events();
    }
}
