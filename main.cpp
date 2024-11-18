#include <Windows.h>

#include "screen.h"

#define INTERVAL 10

int main()
{
    PRINT("My shot at perspective projection of 3D points to a 2D screen\n\n");

    //  TODO:
    // - console width and height correction (done)
    // - rotation (half-done, the formula works!)
    //      - optimize the code
    //      - make it for all axes
    // - controls for depth and rotation
    // - not displaying negative z
    // - absolute coordinates to camera coordinates
    // - threads?

    //      Setup:
    // X and Y axes
    Horizontal_Line hLine(0);
    Vertical_Line vLine(0);

    // objects
    std::vector<Point_3D> points = {
        /*Point_3D( 8, 8, 0),
        Point_3D(-8, 8, 0),
        Point_3D(-8,-8, 0),
        Point_3D( 8,-8, 0)*/
        Point_3D( 12, 0, 0),
        Point_3D( 0, 12, 0),
        Point_3D(-12, 0, 0),
        Point_3D( 0,-12, 0)
    };
    Point_3D position(0, 0, 1);
    Point_3D rotation(0, 0, 30);
    std::vector<Line_2D_Indices> linesIndices = {
        Line_2D_Indices(0, 1),
        Line_2D_Indices(1, 2),
        Line_2D_Indices(2, 3),
        Line_2D_Indices(3, 0)
    };
    bool ifLines = true;

    std::vector<Object_3D> objectVector = {
        Object_3D(points, position, rotation, linesIndices, ifLines)
        //Box( 16, 16, 16, Point_3D(0, 0, 10), Point_3D(0, 0, 30), true)
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
