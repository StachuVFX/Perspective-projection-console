#include <Windows.h>

#include "screen.h"

#define INTERVAL 10

int main()
{
    PRINT("My shot at perspective projection of 3D points to a 2D screen\n\n");

    //  TODO:
    // - code cleaning (done)
    // - rotation
    // - absolute coordinates to camera coordinates
    // - threads?

    //      Setup:
    // X and Y axes
    Horizontal_Line hLine(0);
    Vertical_Line vLine(0);

    // objects
    std::vector<Object_3D> objectVector = {
        // boxes (width, height, depth, position?, ifLines?)
        Box(10,  5, 10, Point_3D(-36, -10, 10), false),
        Box(20, 10, 20, Point_3D(  0,   0, 30))
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
