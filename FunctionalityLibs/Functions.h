#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "Prototypes.h"
#include "Helpers.h"
#include "Structs.h"
#include "../UI/UIPrototypes.h"


#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int StoreHistoryDataInFile(char *Question, char *Response){

    GameHistoryData Data;

    Data.Question = Question;
    Data.Response = Response;

    const char *FileName = "PedritoData.txt";

    FILE *Fp = fopen(FileName, "a+");

    if(!Fp){
        // ClearScreen();
        // gotoxy((Size.columns / 2) - 19, (Size.rows / 2));
        perror("No se pudo abrir el archivo");
        getch();
        ClearScreen();
        return EXIT_FAILURE;
    }

    fprintf(Fp, "%s,%s\n", Data.Question, Data.Response);

    fclose(Fp);
    return EXIT_SUCCESS;
}

int ViewHistoryDataInFile() {

    TerminalSize Size = CalculateTerminalSize();
    GameHistoryData Data;

    // Determine the width and height based on the terminal size
    int Width = Size.columns - StartX * 2 - 2; // Adjusting to fit within the terminal
    int Height = Size.rows - StartY * 2 - 2;   // Adjusting to fit within the terminal

    const int EndX = Width + StartX;
    const int EndY = Height + StartY;

    const char *FileName = "PedritoData.txt";

    FILE *Fp = fopen(FileName, "r");

    if(!Fp){
        ClearScreen();
        gotoxy((Size.columns / 2) - 20, (Size.rows / 2));
        perror("Error al tratar de abrir archivo");
        getch();
        return EXIT_FAILURE; // Return failure if the file could not be opened
    }

    // Check if the file is empty
    if(IsFileEmpty(FileName)){
        ClearScreen();
        DrawRectangleNoSymbolInside(StartX, StartY);
        gotoxy((EndX / 2) - 14, EndY / 2);
        printf("No hay historial disponible.");
        getch();
        fclose(Fp);
        return EXIT_FAILURE; 
    }

    ClearScreen();
    rewind(Fp); 


    DrawRectangleNoSymbolInside(StartX, StartY);

    int row = 2; // Start row for displaying data

    char QuestionAsked[256];
    char ResponseGotten[256];

    while (fscanf(Fp, "%255[^,],%255[^\n]", QuestionAsked, ResponseGotten) == 2) {
        if (row == Height - 6) { // If data exceeds the terminal height
            row = 2;
            gotoxy((EndX / 2) - 16, (EndY - 2));
            printf("Continuar listado, presione cualquier tecla...");
            getch();
            ClearScreen();
            DrawRectangleNoSymbolInside(StartX, StartY);
        }

        gotoxy((Width / 2) + 3, StartY + 1);
        printf("Historial.\n");

        gotoxy((Width / 2) + 3, StartY + row);
        printf("%20s | %20s", QuestionAsked, ResponseGotten);
        row++;
    }

    if (ferror(Fp)) {
        ClearScreen();
        gotoxy((Size.columns / 2) - 14, (Size.rows / 2));
        perror("I/O error leyendo el archivo");
        getch();
        fclose(Fp); 
        return EXIT_FAILURE; 
    }
    
    fclose(Fp);
    getch(); // Wait for the user to press a key before clearing the screen
    ClearScreen();

    return EXIT_SUCCESS; 
}

void GetGameInstructions(void) {
    ClearScreen();
    char *FileName = "Instructions.txt";
    FILE *Fp = fopen(FileName, "r");
    if (Fp == NULL) {
        perror("No se pudo abrir el archivo.");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), Fp)) {
        printf("%s", line);  // Print each line as it is
    }

    fclose(Fp);
}

void PlayGame(){
    ClearScreen();

    char *Petition = NULL;
    char *Question = NULL;
    char *AnswerToQuestion = NULL;
    char Key;

    char *DefaultAnswers[] = {
        "Es en serio?",
        "Busca en google",
        "Disfruta tu soledad",
        "No quieres saber",
        "Eres demasiado inocente.",
        "Que?",
        "No entendi tu pregunta",
        "Te falta calle",
        "No, rey.",
        "Superala.",
        "Estas bien?",
        "Te vas a ir al pozo conmigo."};

    Petition = GetPetition(&AnswerToQuestion);

    if(Petition != NULL){

        Question = GetQuestion();

        if(Question != NULL){
            if (AnswerToQuestion != NULL) {
                printf("\nRespuesta: %s\n", AnswerToQuestion);
                StoreHistoryDataInFile(Question, AnswerToQuestion);
                free(AnswerToQuestion);
            }

            else{
                int Max = 12;
                int Min = 0; 
                int RdNum = rand() % (Max - Min + 1) + Min;

                printf("\nRespuesta: %s\n", DefaultAnswers[RdNum]);

                StoreHistoryDataInFile(Question, DefaultAnswers[RdNum]);
            }
        }

        getch();
    }

    // free(AnswerToQuestion);
    free(Question);
    free(Petition);
}

#endif