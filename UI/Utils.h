#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "UIStructs.h"
#include "UIPrototypes.h"
#include "../FunctionalityLibs/Helpers.h"

#ifndef UTILS_H
#define UTILS_H

bool noKeyPressed(void)
{
    if (kbhit())
    {
        return false;
    }
    return true;
}

TerminalSize CalculateTerminalSize(void){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    TerminalSize window;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    window.rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    window.columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    return window;
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void LoadLoadingBar(char *Message)
{
    int BarLen = 40;

    TerminalSize Size = CalculateTerminalSize();
    const int TerminalMidPointXAxis = (Size.columns / 2) - 23;
    const int TerminalMidPointYAxis = Size.rows / 2;
    const int BarStartX = (Size.columns / 2) - (BarLen / 2); // Center the loading bar horizontally

    // Calculate the position to center the message
    int MessageLength = strlen(Message);
    int MessageStartX = BarStartX + (BarLen / 2) - (MessageLength / 2); // Center the message relative to the loading bar

    // Print the message centered above the loading bar
    gotoxy(MessageStartX, TerminalMidPointYAxis - 1);
    printf("%s", Message);

    for (int i = 0; i <= BarLen; i++)
    {
        int percent = (i * 100) / BarLen; // Calculate percentage
        gotoxy(TerminalMidPointXAxis, TerminalMidPointYAxis); // Move cursor more or less to the center
        printf("\033[34m");    //set color to blue
        printf("[");                                          // Start of the bar

        for (int j = 0; j < i; j++)
        {
            printf("%c", 254); // fill portion when i is not 0 any more
        }

        for (int j = i; j < BarLen; j++)
        {
            printf("."); // fill portion with dots first
        }

        printf("] %d%%", percent); // End of the bar and percentage

        fflush(stdout); /// clear output buffer
        Sleep(50);      // delay

        if (i == BarLen)
        {
            printf("\033[0m\n"); // New line after completion and setting the default color again
        }
    }
}

void DrawRectangle(int startX, int startY, int width, int height, float sleepTime, const char *color)
{
    const int endX = startX + width;
    const int endY = startY + height;
    // Set the console color
    printf("%s", color);

    for (int x = startX; x < endX; x++)
    {
        for (int y = startY; y < endY; y++)
        {
            gotoxy(x, y);
            Sleep(sleepTime);
            printf("%c", 219);
        }
    }
}

void DrawRectangleNoSymbolInside(int startX, int startY)
{

    // Calculate terminal size
    TerminalSize size = CalculateTerminalSize();

    // Determine the width and height based on the terminal size
    int width = size.columns - startX * 2 - 2; // Adjusting to fit within the terminal
    int height = size.rows - startY * 2 - 2;   // Adjusting to fit within the terminal

    int endX = startX + width;
    int endY = startY + height;

    // Draw top side of rectangle
    for (int xInit = startX; xInit <= endX; xInit++)
    {
        gotoxy(xInit, startY);
        printf("%c", 196); // Horizontal line character
    }

    // Draw bottom side of rectangle
    for (int xInit = startX; xInit <= endX; xInit++)
    {
        gotoxy(xInit, endY);
        printf("%c", 196); // Horizontal line character
    }

    // Draw left side of rectangle
    for (int yInit = startY; yInit <= endY; yInit++)
    {
        gotoxy(startX, yInit);
        printf("%c", 179); // Vertical line character
    }

    // Draw right side of rectangle
    for (int yInit = startY; yInit <= endY; yInit++)
    {
        gotoxy(endX, yInit);
        printf("%c", 179); // Vertical line character
    }

    // Draw corners
    gotoxy(startX, startY);
    printf("%c", 218); // Top-left corner

    gotoxy(endX, startY);
    printf("%c", 191); // Top-right corner

    gotoxy(startX, endY);
    printf("%c", 192); // Bottom-left corner

    gotoxy(endX, endY);
    printf("%c", 217); // Bottom-right corner
}

void LoadLogoUni(void){
    // Each rectangle is defined by {startX, startY, width, height}
    int rectangles[][4] = {
        {5, 5, 9, 15},   // First rectangle
        {14, 16, 24, 4}, // Second rectangle
        {29, 10, 9, 10}, // Third rectangle
        {17, 5, 9, 9},   // Fourth rectangle
        {26, 5, 24, 4},  // Fifth rectangle
        {41, 9, 9, 11},  // Sixth rectangle
        {50, 16, 13, 4}, // Seventh rectangle
        {54, 10, 9, 10}, // Eighth rectangle
        {54, 5, 9, 4}    // Ninth rectangle
    };

    while(noKeyPressed()){

        // Delay before starting the glow effect
        Sleep(1500);

        // Set console text color to blue
        printf("\033[0;34m");

        // Loop through each rectangle and draw it
        int numRectangles = sizeof(rectangles) / sizeof(rectangles[0]);
        for (int i = 0; i < numRectangles; i++)
        {
            DrawRectangle(rectangles[i][0], rectangles[i][1], rectangles[i][2], rectangles[i][3], 0.100000, "\033[0;34m");
        }

        // Delay before starting the glow effect
        Sleep(100);

        // Second pass: draw with a brighter color to create a glow effect
        for (int i = 0; i < numRectangles; i++)
        {
            DrawRectangle(rectangles[i][0], rectangles[i][1], rectangles[i][2], rectangles[i][3], 0.100000, "\e[0;37m");
        }

        Sleep(150);

        for (int i = 0; i < numRectangles; i++)
        {
            DrawRectangle(rectangles[i][0], rectangles[i][1], rectangles[i][2], rectangles[i][3], 0.100000, "\033[0;34m");
        }

        // Reset console color
        printf("\033[0m");

        gotoxy(16, 21);
        printf("Presione cualquier letra...");

    }

}

void ShowCredentials(void){
    ClearScreen();

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    TerminalSize size = CalculateTerminalSize();

    DrawRectangleNoSymbolInside(10, 2);

    int XAxis = (size.columns / 2) - 21;
    int YAxis = (size.rows / 2) - 5;
    int XIdPosition = XAxis + 35;

    gotoxy(XAxis, YAxis);
    printf("Proyecto GYM UNI.");

    YAxis += 2;
    gotoxy(XAxis, YAxis);
    printf("Universidad Nacional De Ingenieria.");

    YAxis ++;
    gotoxy(XAxis, YAxis);
    printf("Area de estudio: DACTIC.");

    YAxis ++;
    gotoxy(XAxis, YAxis);
    printf("Kenry Onell Lira Zavala");
    gotoxy(XIdPosition, YAxis);
    printf("2024-1898U.");


    YAxis ++;
    gotoxy(XAxis, YAxis);
    printf("Gustavo Adolfo Orozco Jarquin");
    gotoxy(XIdPosition, YAxis);
    printf("2024-1938U.");

    YAxis++;
    gotoxy(XAxis, YAxis);
    printf("Aryan Sidar Narvaez Rivera");
    gotoxy(XIdPosition, YAxis);
    printf("2024-1896U.");
    
    YAxis += 2;
    gotoxy(XAxis, YAxis);
    printf("Docente: Ing.Nelson Barrios.");

    YAxis += 2;
    gotoxy(XIdPosition, YAxis);
    printf("%d/%02d/%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
   

    getch();
}


#endif