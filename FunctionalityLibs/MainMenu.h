#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#include "Prototypes.h"
#include "Helpers.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_TAB 9

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

void DisplayMainMenu(int Option) {
    // ClearScreen();
    DrawRectangleNoSymbolInside(StartX, StartY);

    gotoxy(StartX + 2, StartY + 1);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("Bienvenido a Pedro responde.\n");

    for (int i = 1; i <= 5; i++) {
        gotoxy(StartX + 2, StartY + 1 + i);
        
        if (i == Option) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("-> "); // Flecha para la opción seleccionada
        } else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            printf("   "); // Espacio para mantener alineación incluso sin la flecha de seleccion
        }

        printf("[%d]. %s", i, 
               (i == 1) ? "Jugar.\n" :
               (i == 2) ? "Ver historial de preguntas y respuestas.\n" :
               (i == 3) ? "Como Jugar?.\n":
               (i == 4) ? "Creditos.\n":
               "Salir.\n");
    }
    gotoxy(StartX + 2, StartY + 7);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("Usar las flechas up/down para desplazarse, Enter para seleccionar.");
}


void MoveTroughMainMenu(void){

    int Option = 1;
    
    ClearScreen();
    while (true)
    {
        DisplayMainMenu(Option);

        int Key = _getch();


        if (Key == 0 || Key == 224)
        {
            // Arrow keys return a two-part key code (0 or 224 followed by the actual key code)
            Key = _getch(); // Get the actual key code
        }

        switch (Key)
        {
            case KEY_UP:
                if(Option > 1){
                    Option--;
                }
                break;

            case KEY_DOWN:
                if (Option < 5){
                    Option++;
                }
                break;

            case KEY_ENTER:
                switch (Option)
                {
                    case 1:
                        PlayGame();
                        ClearScreen();
                        break;
                    case 2:
                        ViewHistoryDataInFile();
                        LoadLoadingBar("Volviendo...");
                        ClearScreen();
                        break;

                    case 3:
                        ClearScreen();
                        GetGameInstructions();
                        getch();
                        ClearScreen();
                        LoadLoadingBar("Volviendo...");
                        ClearScreen();
                        break;

                    case 4:
                        ClearScreen();
                        ShowCredentials();
                        ClearScreen();
                        LoadLoadingBar("Volviendo...");
                        ClearScreen();
                        break;

                    case 5:
                        ClearScreen();
                        LoadLoadingBar("Saliendo del programa...");
                        return;
                }
                break;
        }

    }
}


#endif

