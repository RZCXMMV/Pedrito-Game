#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "Prototypes.h"
#include "Helpers.h"
#include "Structs.h"


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

    int Width = Size.columns - StartX * 2 - 2;
    int Height = Size.rows - StartY * 2 - 2;

    const int EndX = Width + StartX;
    const int EndY = Height + StartY;

    const int QuestionWidth = Width / 2 - 3;
    const int AnswerWidth = Width / 2 - 3;

    const char *FileName = "PedritoData.txt";

    FILE *Fp = fopen(FileName, "r");

    if (!Fp) {
        ClearScreen();
        gotoxy((Size.columns / 2) - 20, (Size.rows / 2));
        printf("\033[0;31mError al tratar de abrir archivo\033[0m\n");
        getch();
        ClearScreen();
        return EXIT_FAILURE;
    }

    if (IsFileEmpty(FileName)) {
        ClearScreen();
        DrawRectangleNoSymbolInside(StartX, StartY);
        gotoxy((EndX / 2) - 14, EndY / 2);
        printf("\033[0;31mNo hay historial disponible.\033[0m\n");
        getch();
        ClearScreen();
        fclose(Fp);
        return EXIT_FAILURE;
    }

    ClearScreen();
    rewind(Fp);
    DrawRectangleNoSymbolInside(StartX, StartY);

    // Print headers
    gotoxy(StartX + 2, StartY + 1);
    printf("\033[0;31m%-*s | %-*s\033[0m", QuestionWidth, "Pregunta", AnswerWidth, "Respuesta");

    char QuestionAsked[256];
    char ResponseGotten[256];

    int row = 3;  // Start displaying from row 3

    while (fscanf(Fp, " %255[^,], %255[^\n]", QuestionAsked, ResponseGotten) == 2) {
        if (row >= Height - 3) {  // If row limit reached, paginate
            gotoxy((EndX / 2) - 16, (EndY - 2));
            printf("\033[0;31mContinuar listado, presione cualquier tecla...\033[0m");
            getch();
            ClearScreen();
            DrawRectangleNoSymbolInside(StartX, StartY);

            // Redraw headers
            gotoxy(StartX + 2, StartY + 1);
            printf("\033[0;31m%-*s | %-*s\033[0m", QuestionWidth, "Pregunta", AnswerWidth, "Respuesta");

            row = 3;  // Reset row position
        }

        // Limit text to fit in the column width and add ellipsis if needed
        char TruncatedQuestion[QuestionWidth + 1];
        char TruncatedResponse[AnswerWidth + 1];

        strncpy(TruncatedQuestion, QuestionAsked, QuestionWidth);
        strncpy(TruncatedResponse, ResponseGotten, AnswerWidth);

        TruncatedQuestion[QuestionWidth] = '\0';
        TruncatedResponse[AnswerWidth] = '\0';

        if (strlen(QuestionAsked) > QuestionWidth) {
            strcpy(&TruncatedQuestion[QuestionWidth - 3], "...");
        }
        if (strlen(ResponseGotten) > AnswerWidth) {
            strcpy(&TruncatedResponse[AnswerWidth - 3], "...");
        }

        // Print the truncated question and response
        gotoxy(StartX + 2, StartY + row);
        printf("%-*s | %-*s", QuestionWidth, TruncatedQuestion, AnswerWidth, TruncatedResponse);

        row++;  // Move to the next row
    }

    if (ferror(Fp)) {
        ClearScreen();
        gotoxy((Size.columns / 2) - 14, (Size.rows / 2));
        printf("\033[0;31mI/O Error leyendo el archivo\033[0m\n");
        getch();
        ClearScreen();
        fclose(Fp);
        return EXIT_FAILURE;
    }

    fclose(Fp);
    getch();
    ClearScreen();

    return EXIT_SUCCESS;
}


void GetGameInstructions(void) {
    ClearScreen();
    char *FileName = "Instructions.txt";
    FILE *Fp = fopen(FileName, "r");
    if (Fp == NULL) {
        gotoxy(35,16);
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

                gotoxy(StartX + 2, StartY + 4);
                printf("Respuesta: %s", AnswerToQuestion);
                StoreHistoryDataInFile(Question, AnswerToQuestion);
                free(AnswerToQuestion);
            }

            else{
                int Max = 12;
                int Min = 0; 
                int RdNum = rand() % (Max - Min + 1) + Min;
                
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                gotoxy(StartX + 2, StartY + 4);
                printf("Respuesta: %s", DefaultAnswers[RdNum]);
                getch();
                ClearScreen();

                StoreHistoryDataInFile(Question, DefaultAnswers[RdNum]);
            }
        }

        getch();
    }

    // free(AnswerToQuestion);
    free(Question);
    free(Petition);
    ClearScreen();
}

#endif