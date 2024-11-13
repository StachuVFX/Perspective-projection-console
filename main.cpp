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
#define Z_MOVE_MARG 10
#define INTERVAL 100
#define TIME 1000 / INTERVAL * 10

int main()
{
    PRINT("My shot at perspective projection of 3D points to a 2D screen\n\n");

    //  TODO:
    // - optimalize display even more (done)
    // - threads + keyboard events
    // - absolute coordinates to camera coordinates

    //      Setup:
    // lines
    Horizontal_Line hLine(0);
    Vertical_Line vLine(0);

    // boxes (width, height, depth, x, y, z, ifLines)
    std::vector<Box> boxVector = {
        Box(20, 10, 20, 0, 0, 30, true)
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
    
    // game loop
    boxVector[0].move(-X_MOVE_MARG / 2, -Y_MOVE_MARG / 2, 0);
    for (int i = 0, j = 0, k = 0, xMove = X_MOVE, yMove = Y_MOVE, zMove = Z_MOVE; i < TIME; i++)
    {
        // clear the screen
        screen.clear();

        // draw lines
        screen.draw(hLine, '-');
        screen.draw(vLine, '|');

        // animate objects
        boxVector[0].move(xMove, yMove, zMove);
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
        }

        // draw objects
        screen.draw(boxVector, 'o');

        // debug lines
        //screen.draw(lineVector, '.');

        // display
        Sleep(INTERVAL);
        screen.display();
    }
}
