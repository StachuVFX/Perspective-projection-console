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
    // - drawing multiple objects
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
    /*std::vector<Point_3D> point_3d_vector = {
        Point_3D(H_SHIFT-PX  ,V_SHIFT-PY  ,     PZ1+D_SHIFT),
        Point_3D(H_SHIFT+PX-1,V_SHIFT-PY  ,     PZ1+D_SHIFT),
        Point_3D(H_SHIFT+PX-1,V_SHIFT+PY-1,     PZ1+D_SHIFT),
        Point_3D(H_SHIFT-PX  ,V_SHIFT+PY-1,     PZ1+D_SHIFT),
        Point_3D(H_SHIFT-PX  ,V_SHIFT-PY  , PZ1+PZ2+D_SHIFT),
        Point_3D(H_SHIFT+PX-1,V_SHIFT-PY  , PZ1+PZ2+D_SHIFT),
        Point_3D(H_SHIFT+PX-1,V_SHIFT+PY-1, PZ1+PZ2+D_SHIFT),
        Point_3D(H_SHIFT-PX  ,V_SHIFT+PY-1, PZ1+PZ2+D_SHIFT)
    };*/
    // boxes (x, y, z, width, height, depth)
    Box box1(0, 0, 30, 30, 16, 30);
    Box box2(-36, -10, 10, 10, 5, 10);
    Box box3( 36, -10, 10, 10, 5, 10);
    Box box4( 36,  10, 10, 10, 5, 10);
    Box box5(-36,  10, 10, 10, 5, 10);

    //      Drawing:
    // screen
    Screen screen(WIDTH, HEIGHT, 90);
    // fill
    //screen.fill('.');

    // draw lines
    screen.draw(hLine, '-');
    screen.draw(vLine, '|');
    // draw points
    //screen.draw(point_2d_vector, 'O');
    //screen.draw(point_3d_vector, 'o');
    screen.draw(box1.normalizedPoints(), 'o');
    screen.draw(box2.normalizedPoints(), 'o');
    screen.draw(box3.normalizedPoints(), 'o');
    screen.draw(box4.normalizedPoints(), 'o');
    screen.draw(box5.normalizedPoints(), 'o');

    // display
    screen.display();
}
