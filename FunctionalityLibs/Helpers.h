#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>



#ifndef HELPERS_H
#define HELPERS_H


void ClearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void ClearScreen(void){
    system("cls");
}


#endif