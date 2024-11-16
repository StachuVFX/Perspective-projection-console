#include <Windows.h>

#include "screen.h"

//#define PX 20
//#define PY 10
//#define PZ1 1
//#define PZ2 40
//#define H_SHIFT 10
//#define V_SHIFT 2
//#define D_SHIFT 0
#define X_MOVE 3
#define Y_MOVE 1
#define Z_MOVE 0
#define X_MOVE_MARG 140
#define Y_MOVE_MARG 28
#define Z_MOVE_M
//#define X_MOVE_MARG 0
//#define Y_MOVE_MARG 0
//#define Z_MOVE_MARG 0
#define INTERVAL 10
#define TIME 1000 / INTERVAL * 60
//#define TIME 1

int main()
{
    PRINT("My shot at perspective projection of 3D points to a 2D screen\n\n");

    //  TODO:
    // - box class actually inheriting object class (done)
    // - better movement - object vector inside screen class (done)
    // - code cleaning
    // - rotation
    // - absolute coordinates to camera coordinates
    // - threads?

    //      Setup:
    // lines
    Horizontal_Line hLine(0);
    Vertical_Line vLine(0);

    // boxes (width, height, depth, position?, ifLines?)
    std::vector<Object_3D> objectVector = {
        Box(20, 10, 20, Point_3D(0, 0, 30))
        /*Box(10, 5, 10, -36, -10, 10),
        Box(10, 5, 10,  36, -10, 10),
        Box(10, 5, 10,  36,  10, 10),
        Box(10, 5, 10, -36,  10, 10)*/
    };

    // lines (for debugging)
    /*std::vector<Line_2D> lineVector = {
        Line_2D(Point_2D(-20, -10), Point_2D( 20, -10)),
        Line_2D(Point_2D( 20, -10), Point_2D( 20,  10)),
        Line_2D(Point_2D( 20,  10), Point_2D(-20,  10)),
        Line_2D(Point_2D(-20,  10), Point_2D(-20, -10))
    };*/

    //      Drawing:
    // screen
    Screen screen(WIDTH, HEIGHT, FOV);

    // add objects
    screen.add_objects(objectVector);
    
    // game loop
    //boxVector[0].move(-X_MOVE_MARG / 2, -Y_MOVE_MARG / 2, 0);
    for (int i = 0, j = 0, k = 0, xMove = X_MOVE, yMove = Y_MOVE, zMove = Z_MOVE; i < TIME && screen.isRunning; i++)
    {
        // clear the screen
        screen.clear();

        // draw lines
        screen.draw_line_horizontal(hLine, '-');
        screen.draw_line_vertical(vLine, '|');

        // animate objects
        /*boxVector[0].move(xMove, yMove, zMove);
        j++;
        if (j >= X_MOVE_MARG / X_MOVE)
        {
            xMove *= -1;
            j = 0;
        }
        k++;
        if (k >= Y_MOVE_MARG / Y_MOVE)
        {
            yMove *= -1;
            k = 0;
        }*/

        // draw objects
        screen.draw();

        // debug lines
        //screen.draw(lineVector, '.');

        // display
        Sleep(INTERVAL);
        screen.display();

        // keyboard events check
        screen.keyboard_events();
    }
}
