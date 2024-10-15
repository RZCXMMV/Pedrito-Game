#include <stdio.h>

#include "FunctionalityLibs/MainMenu.h"
#include "FunctionalityLibs/Functions.h"
#include "UI/Utils.h"

int main(void){

    ClearScreen();
    LoadLogoUni();
    ClearInputBuffer();

    //Principal Menu
    MoveTroughMainMenu();

    return 0;
}