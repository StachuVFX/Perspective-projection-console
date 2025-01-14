#include <Windows.h>
#include <fstream>
#include <string>

#include "screen.h"

#define MODELS_FILENAME "models.json"
#define OBJECTS_FILENAME "objects.json"

#define INTERVAL 10

int main()
{
    PRINT("My shot at perspective projection of 3D points to a 2D screen\n\n");

    //  TODO:
    // - not displaying negative z (done)
    // - read objects from a file
    //      - make example files in JSON (done)
    //      - reading the files
    //      - converting file content to objects
    // - make proper rotation using vectors
    // - absolute coordinates to camera coordinates
    // - threads?

    //      Setup:
    // X and Y axes
    Horizontal_Line hLine(0);
    Vertical_Line vLine(0);

    /*std::vector<Point_3D> pyramid = {
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
    bool pyramid_ifLines = true;*/

    //std::vector<Object_3D> objectVector = {
    //    //Box( 32, 32, 32, Point_3D(0, 0, 40), Point_3D(0, 0, 0), true)
    //    Object_3D(pyramid, pyramid_position, pyramid_rotation, pyramid_linesIndices, pyramid_ifLines)
    //};
    std::vector<Object_3D> objectVector;

    //      Reading object files
    std::ifstream objectsFile(OBJECTS_FILENAME);
    std::ifstream modelsFile(MODELS_FILENAME);

    std::string textLine;
    while (getline(objectsFile, textLine))
    {
        if (textLine.find("\"objects\""))
        {
            while (getline(objectsFile, textLine))
            {
                if (textLine.find("{"))
                {
                    char name[30];
                    while (getline(objectsFile, textLine))
                    {

                    }
                }
            }
        }
    }

    modelsFile.close();
    objectsFile.close();

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
        //screen.draw_lines_2d(lineVector);

        // display
        Sleep(INTERVAL);
        screen.display();

        // keyboard events
        screen.keyboard_events();
    }
}
