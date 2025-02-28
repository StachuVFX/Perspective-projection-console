#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

#include "screen.h"

#define MODELS_FILENAME "C:\\Programming\\Stachu\\Perspective-projection-console\\models.txt"
#define OBJECTS_FILENAME "C:\\Programming\\Stachu\\Perspective-projection-console\\objects.txt"

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

    std::vector<Object_3D> objectVector = {
        //Box( 32, 32, 32, Point_3D(0, 0, 40), Point_3D(0, 0, 0), true)
        Object_3D(pyramid, pyramid_position, pyramid_rotation, pyramid_linesIndices, pyramid_ifLines)
    };
    //std::vector<Object_3D> objectVector;

    //      Reading object files
    std::ifstream objectsFile(OBJECTS_FILENAME);
    //std::ifstream modelsFile(MODELS_FILENAME);

    std::string textLine;
    while (getline(objectsFile, textLine))
    {
        if (!textLine.empty())
        {
            std::string modelName;
            std::string objectName;
            double scale = 1.0;
            Point_3D position;
            Point_3D rotation;
            std::string tmpString;
            int startIndex;

            getline(objectsFile, textLine);
            while (!textLine.empty())
            {
                if (textLine.compare("model\:") == 0)
                {
                    getline(objectsFile, textLine);
                    startIndex = textLine.find_first_not_of(" ");
                    modelName = textLine.substr(startIndex, textLine.length() - startIndex);
                }
                else if (textLine.compare("name\:") == 0)
                {
                    getline(objectsFile, textLine);
                    startIndex = textLine.find_first_not_of(" ");
                    objectName = textLine.substr(startIndex, textLine.length() - startIndex);
                }

                else if (textLine.compare("values\:") == 0)
                {
                    if (textLine.compare("    scale\:") == 0)
                    {
                        getline(objectsFile, textLine);
                        startIndex = textLine.find_first_not_of(" ");
                        scale = std::stod(textLine.substr(startIndex, textLine.length() - startIndex));
                    }
                    else if (textLine.compare("    position\:") == 0)
                    {
                        getline(objectsFile, textLine);
                        startIndex = textLine.find_first_not_of(" ");
                        tmpString = textLine.substr(startIndex, textLine.length() - startIndex);
                        position.x = std::stod(tmpString.substr(
                            0,
                            tmpString.find_first_of(",")
                        ));
                        position.y = std::stod(tmpString.substr(
                            tmpString.find_first_of(" ") + 1,
                            tmpString.find_last_of(",") - (tmpString.find_first_of(" ") + 1)
                        ));
                        position.z = std::stod(tmpString.substr(
                            tmpString.find_last_of(" ") + 1,
                            tmpString.length() - (tmpString.find_last_of(" ") + 1)
                        ));
                    }
                    else if (textLine.compare("    rotation\:") == 0)
                    {
                        getline(objectsFile, textLine);
                        startIndex = textLine.find_first_not_of(" ");
                        tmpString = textLine.substr(startIndex, textLine.length() - startIndex);
                        rotation.x = std::stod(tmpString.substr(
                            0,
                            tmpString.find_first_of(",")
                        ));
                        rotation.y = std::stod(tmpString.substr(
                            tmpString.find_first_of(" ") + 1,
                            tmpString.find_last_of(",") - (tmpString.find_first_of(" ") + 1)
                        ));
                        rotation.z = std::stod(tmpString.substr(
                            tmpString.find_last_of(" ") + 1,
                            tmpString.length() - (tmpString.find_last_of(" ") + 1)
                        ));
                    }
                }
            }
            
            if (modelName.compare("\tcube") == 0)
            {
                Box cube(scale, scale, scale, position, rotation, true);
                objectVector.push_back(cube);
            }
            else if (modelName.compare("\tpyramid") == 0)
            {
                std::vector<Point_3D> points = {
                    Point_3D(-1, -1, -0.5773502691896258),
                    Point_3D(1, -1, -0.5773502691896258),
                    Point_3D(1, 1, -0.5773502691896258),
                    Point_3D(-1, 1, -0.5773502691896258),
                    Point_3D(0, 0, 1.154700538379252)
                };
                std::vector<Line_2D_Indices> lines = {
                    Line_2D_Indices(0, 1),
                    Line_2D_Indices(1, 2),
                    Line_2D_Indices(2, 3),
                    Line_2D_Indices(3, 0),
                    Line_2D_Indices(0, 4),
                    Line_2D_Indices(1, 4),
                    Line_2D_Indices(2, 4),
                    Line_2D_Indices(3, 4)
                };
                Object_3D pyramid(points, position, rotation, lines, true);
                objectVector.push_back(pyramid);
            }
        }
    }

    //modelsFile.close();
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
