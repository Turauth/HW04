#include "raylib.h"
#include <iostream>
#include <vector>

int main(void)
{
    // Make a window with a certain width and height, and set it to display at 60 FPS.
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Rectangle Sandbox");
    SetTargetFPS(60);

    // Initialize stuff that will be used later.
    int releaseCount = 0;
    std::vector<int> mouseX1{};
    std::vector<int> mouseY1{};
    std::vector<int> mouseX2{};
    std::vector<int> mouseY2{};
    std::vector<int> recX{};
    std::vector<int> recY{};
    std::vector<int> recW{};
    std::vector<int> recH{};
    std::vector<Color> colors{ BLUE, GREEN, YELLOW, RED, BROWN};
    std::vector<Color> currentColor{};
    int colorIter = 0;
    int recs = 0;
    int delRecs = 0;

    // Make a loop that runs continuously until the window close button or ESC key are pressed.
    while (!WindowShouldClose())
    {   
        // Track the mouse position in the window until the window is closed.
        Vector2 mousePos = GetMousePosition();

        // Whenever the left mouse button is released, execute the code in this block.
        if (IsMouseButtonReleased(0))
        {
            ++releaseCount;

            // Check whether the release count is even or odd 
            // (https://www.geeksforgeeks.org/cpp-program-to-check-whether-number-is-even-or-odd/).
            if (releaseCount % 2 == 0)
            {
                // If the release count is even, the release corresponds to the second click that should be used to
                // generate a rectangle. This second click has associated coordinates that should be added to respective
                // vectors storing the coordinates of the cursor upon all even clicks.
                mouseX2.push_back(mousePos.x);
                mouseY2.push_back(mousePos.y);

                // Another rectangle should be added to the window after each second click.
                ++recs;
                
                // The following four "if" or "else if" statements should set the coordinates of the top left corner of the 
                // newest rectangle (recX and recY) along with its width and height (recW and recH).
                if (mouseX1[mouseX1.size() - 1] > mouseX2[mouseX2.size() - 1] 
                && mouseY1[mouseY1.size() - 1] > mouseY2[mouseY2.size() - 1])
                {
                    recX.push_back(mouseX2[mouseX2.size() - 1]);
                    recY.push_back(mouseY2[mouseY2.size() - 1]);
                    recW.push_back(mouseX1[mouseX1.size() - 1] - mouseX2[mouseX2.size() - 1]);
                    recH.push_back(mouseY1[mouseY1.size() - 1] - mouseY2[mouseY2.size() - 1]);
                }
                else if (mouseX1[mouseX1.size() - 1] > mouseX2[mouseX2.size() - 1] 
                && mouseY1[mouseY1.size() - 1] < mouseY2[mouseY2.size() - 1])
                {
                    recX.push_back(mouseX2[mouseX2.size() - 1]);
                    recY.push_back(mouseY1[mouseY1.size() - 1]);
                    recW.push_back(mouseX1[mouseX1.size() - 1] - mouseX2[mouseX2.size() - 1]);
                    recH.push_back(mouseY2[mouseY2.size() - 1] - mouseY1[mouseY1.size() - 1]);
                }
                else if (mouseX1[mouseX1.size() - 1] < mouseX2[mouseX2.size() - 1] 
                && mouseY1[mouseY1.size() - 1] > mouseY2[mouseY2.size() - 1])
                {
                    recX.push_back(mouseX1[mouseX1.size() - 1]);
                    recY.push_back(mouseY2[mouseY2.size() - 1]);
                    recW.push_back(mouseX2[mouseX2.size() - 1] - mouseX1[mouseX1.size() - 1]);
                    recH.push_back(mouseY1[mouseY1.size() - 1] - mouseY2[mouseY2.size() - 1]);
                }
                else if (mouseX1[mouseX1.size() - 1] < mouseX2[mouseX2.size() - 1] 
                && mouseY1[mouseY1.size() - 1] < mouseY2[mouseY2.size() - 1])
                {
                    recX.push_back(mouseX1[mouseX1.size() - 1]);
                    recY.push_back(mouseY1[mouseY1.size() - 1]);
                    recW.push_back(mouseX2[mouseX2.size() - 1] - mouseX1[mouseX1.size() - 1]);
                    recH.push_back(mouseY2[mouseY2.size() - 1] - mouseY1[mouseY1.size() - 1]);
                }

                // The color of the newest rectangle should be added to the vector of colors corresponding to each rectangle in
                // the window (currentColor), and the index of the added color should correspond to those of recX, recY, recW,
                // and recH.
                currentColor.push_back(colors[colorIter]);

                // Five colors should be cycled through when generating rectangles, so the following "if" and "else"
                // statements should serve to iterate through that list of colors being added to the currentColor vector.
                if (colorIter <= 3)
                    ++colorIter;
                else
                    colorIter = 0;
            }

            // If times the left mouse button has been released is odd, the coordinates of the cursor at the last click should
            // be added to corresponding vectors.
            else
            {
                mouseX1.push_back(mousePos.x);
                mouseY1.push_back(mousePos.y);
            }
        }

        // Variable recs should always equal the number of rectangles being displayed on the window, but it should also be
        // one greater than the indices of recX, recY, recW, recH, and currentColor. For each rectangle being displayed,
        // check whether the conditions for rectangle deletion are met. The displayed rectangles are iterated through
        // backwards because if iteration started at zero, then the indices of the rectangle vectors corresponding
        // to certain rectangles could trickle down after passes through the for loop.
        for (int i{ recs - 1 }; i >= 0; --i)
        {
            // If the delete key is being released and the cursor is in the area of the  rectangle, ...
            if (IsKeyReleased(KEY_DELETE) && 
            mousePos.x > recX[i] &&
            mousePos.x < recX[i] + recW[i] &&
            mousePos.y > recY[i] &&
            mousePos.y < recY[i] + recH[i])
            {
                // ... remove the x and y coordinates, the width, the height, and the color used to draw the rectangle from 
                // the respective vectors.
                recX.erase(recX.begin() + i);
                recY.erase(recY.begin() + i);
                recW.erase(recW.begin() + i);
                recH.erase(recH.begin() + i);
                currentColor.erase(currentColor.begin() + i);
                ++delRecs;
            }
        }

        // Update the number of rectangles being displayed on the window.
        recs = recs - delRecs;
        delRecs = 0;

        // Draw stuff.
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            // If rectangles have been generated, display them on the window.
            if (recs > 0)
                for (int i{ 0 }; i < recs; ++i)
                    DrawRectangle(recX[i], recY[i], recW[i], recH[i], currentColor[i]);

        EndDrawing();
    }

    // When the window close button or ESC key are pressed, close the window and OpenGL context.
    CloseWindow();

    return 0;
}