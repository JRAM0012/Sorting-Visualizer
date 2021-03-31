#include <stdlib.h>    // for exit(0) in android and srand() seed 
#include <time.h>      // for srand

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"



#ifdef PLATFORM_ANDROID
    #define SCREENWIDTH 1600
    #define SCREENHEIGHT 720
    #define TOTALBARS 200
#else
    #define SCREENWIDTH 700
    #define SCREENHEIGHT 512
#endif // PLATFORM_ANDROID


#ifndef TOTALBARS
    #define TOTALBARS 200
#endif
#define BARCLIPLENGTH 200
int bars[TOTALBARS];


int main()
{
    int screenWidth = SCREENWIDTH, screenHeight = SCREENHEIGHT;
    InitWindow(screenWidth, screenHeight, "Sorting Visualizer");
#ifdef PLATFORM_ANDROID
    GuiSetStyle(DEFAULT, TEXT_SIZE, 56);
#endif
    bool start = false;
    bool firsttime = true;
    bool sort = false;
    int sortingindex = 0;
    int BarSpacing = 3;
    int shifter = 12;
    srand(time(NULL));
    for(int i = 0; i < TOTALBARS; i++)
    {
        bars[i] = rand() % BARCLIPLENGTH;
        bars[i] = bars[i] > 1 ? bars[i] : rand() % BARCLIPLENGTH;
    }

    while (!WindowShouldClose())
    {
        if(start || IsKeyPressed(KEY_R))
        {
            firsttime = false;
            srand(time(NULL));
            for(int i = 0; i < TOTALBARS; i++)
            {
                bars[i] = rand() % BARCLIPLENGTH;
                bars[i] = bars[i] > 1 ? bars[i] : rand() % BARCLIPLENGTH;
            }
            sort = true;
            sortingindex = 0;
        }
        if(sort)
        {
            if(bars[sortingindex] > bars[sortingindex + 1])
            {
                int temp = bars[sortingindex];
                bars[sortingindex] = bars[sortingindex + 1];
                bars[sortingindex + 1] = temp;
            }
            sortingindex++;
            if(sortingindex > TOTALBARS - 2)
                sortingindex = 0;
        }

        BeginDrawing();
        ClearBackground(BLACK);
#ifdef PLATFORM_ANDROID
        start = GuiButton((Rectangle) {220, 100, 255, 105}, firsttime ? "START" : "RESTART");
#else
        start = GuiButton((Rectangle) {120, 10, 65, 25}, firsttime ? "START" : "RESTART");
#endif
        for(int i = 0; i < TOTALBARS; i++)
            DrawLine( i * BarSpacing + shifter, screenHeight - 50,  i * BarSpacing + shifter, screenHeight - 50 - bars[i] , RED);
        if(sort) DrawText("SORTING", 520, 120, 21, RED);
        EndDrawing();
        if(IsKeyPressed(KEY_BACK)) break;
    }
    
    CloseWindow();
    exit(0);
    return 0;
}





