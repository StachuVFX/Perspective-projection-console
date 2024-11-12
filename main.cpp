#include "screen.h"

#define PX 20
#define PY 10
#define PZ1 1
#define PZ2 40
#define H_SHIFT 10
#define V_SHIFT 2
#define D_SHIFT 0

int main()
{
    PRINT("My shot at perspective projection of 3D points to a 2D screen\n\n");

    //  TODO:
    // - objects
    // - game loop + animation
    // - threads + keyboard events
    // - absolute coordinates to camera coordinates

    //      Setup:
    // lines
    Horizontal_Line hLine(0);
    Vertical_Line vLine(0);

    // 2D points vector
    /*std::vector<Point_2D> point_2d_vector = {
        Point_2D(0, 9),
        Point_2D(0, -10),
        Point_2D(19, 0),
        Point_2D(-20, 0)
    };*/
    // 3D points vector
    std::vector<Point_3D> point_3d_vector = {
        Point_3D(H_SHIFT-PX  ,V_SHIFT-PY  ,     PZ1+D_SHIFT),
        Point_3D(H_SHIFT+PX-1,V_SHIFT-PY  ,     PZ1+D_SHIFT),
        Point_3D(H_SHIFT+PX-1,V_SHIFT+PY-1,     PZ1+D_SHIFT),
        Point_3D(H_SHIFT-PX  ,V_SHIFT+PY-1,     PZ1+D_SHIFT),
        Point_3D(H_SHIFT-PX  ,V_SHIFT-PY  , PZ1+PZ2+D_SHIFT),
        Point_3D(H_SHIFT+PX-1,V_SHIFT-PY  , PZ1+PZ2+D_SHIFT),
        Point_3D(H_SHIFT+PX-1,V_SHIFT+PY-1, PZ1+PZ2+D_SHIFT),
        Point_3D(H_SHIFT-PX  ,V_SHIFT+PY-1, PZ1+PZ2+D_SHIFT)
    };

    //      Drawing:
    // screen
    Screen screen(WIDTH, HEIGHT, 90);
    // fill
    //screen.Fill('.');

    // draw lines
    screen.Draw(hLine, '-');
    screen.Draw(vLine, '|');
    // draw points
    //screen.Draw(point_2d_vector, 'O');
    screen.Draw(point_3d_vector, 'o');

    // display
    screen.Display();
}
