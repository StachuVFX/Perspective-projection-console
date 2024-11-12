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
#define X_MOVE_MARG 100
#define Y_MOVE_MARG 24
#define Z_MOVE_MARG 10
#define INTERVAL 200

int main()
{
    PRINT("My shot at perspective projection of 3D points to a 2D screen\n\n");

    //  TODO:
    // - drawing lines
    // - optimalize display
    // - threads + keyboard events
    // - absolute coordinates to camera coordinates

    //      Setup:
    // lines
    Horizontal_Line hLine(0);
    Vertical_Line vLine(0);

    // boxes (x, y, z, width, height, depth)
    std::vector<Box> boxVector = {
        Box(0, 0, 30, 20, 10, 30)
        /*Box(-36, -10, 10, 10, 5, 10),
        Box( 36, -10, 10, 10, 5, 10),
        Box( 36,  10, 10, 10, 5, 10),
        Box(-36,  10, 10, 10, 5, 10)*/
    };

    //      Drawing:
    // screen
    Screen screen(WIDTH, HEIGHT, 90);
    // fill
    //screen.fill('.');

    // draw lines
    //screen.draw(hLine, '-');
    //screen.draw(vLine, '|');
    
    // draw objects
    //screen.draw(boxVector, 'o');

    // display
    //screen.display();
    
    boxVector[0].move(-X_MOVE_MARG / 2, -Y_MOVE_MARG / 2, 0);
    for (int i = 0, j = 0, k = 0, xMove = X_MOVE, yMove = Y_MOVE, zMove = Z_MOVE; i < 100; i++)
    {
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

        // display
        Sleep(INTERVAL);
        screen.display();
    }
}
