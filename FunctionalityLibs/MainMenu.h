#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#include "Prototypes.h"
#include "Helpers.h"
#include "../UI/UIPrototypes.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_TAB 9

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

void DisplayMainMenu(int Option) {

    printf("Bienvenido a Pedro responde.\n");

    for (int i = 1; i <= 5; i++) {
        
        if (i == Option) {
            printf("-> ");
        } 
        
        else {
            printf("   ");
        }

        printf("[%d]. %s", i, 
               (i == 1) ? "Jugar.\n" :
               (i == 2) ? "Ver historial de preguntas y respuestas.\n" :
               (i == 3) ? "Como Jugar?.\n":
               (i == 4) ? "Creditos.\n":
               "Salir.\n");
    }

    printf("Usar las flechas up/down para desplazarse, Enter para seleccionar.");
}


void MoveTroughMainMenu(void){

    int Option = 1;

    while (true)
    {
        ClearScreen();
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
                        break;
                    case 2:
                        ViewHistoryDataInFile();
                        getch();
                        break;

                    case 3:
                        GetGameInstructions();
                        getch();
                        break;

                    case 4:
                        ShowCredentials();
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

