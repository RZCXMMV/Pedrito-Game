#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include "../UI/UIPrototypes.h"


#ifndef HELPERS_H
#define HELPERS_H

#define StartX 10
#define StartY 5

void ClearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void ClearScreen(void){
    system("cls");
}

bool IsFileEmpty(const char *FileName)
{
    FILE *Fp = fopen(FileName, "r");

    if(!Fp){
        perror("No se pudo abrir el archivo");
        return EXIT_FAILURE;
    }

    fseek(Fp, 0, SEEK_END);  // Move the file position indicator to the end of the file
    long fileSize = ftell(Fp);  // Get the current position of the file position indicator

    if (fileSize == 0) {
        // File is empty
        fclose(Fp);
        return true;
    } else {
        // File is not empty
        fclose(Fp);
        return false;  
    }
}

char *GetPetition(char **AnswerToQuestion) {
    TerminalSize Dimensions = CalculateTerminalSize();

    // Determine the width and height based on the terminal size
    int Width = Dimensions.columns - StartX * 2 - 2; // Adjusting to fit within the terminal
    int Height = Dimensions.rows - StartY * 2 - 2;   // Adjusting to fit within the terminal

    char *PetitionAutoLarge = "Pedro por favor responde esta pregunta";
    char *PetitionAutoShort = "Pedro por favor responde";
    int InitialSize = 10;
    int LengthOfString = 0;
    char *StringPetition = (char *) malloc(InitialSize * sizeof(char));
    if (StringPetition == NULL) {
        gotoxy((Width / 2) - 5, Height / 2);
        printf("Error al reservar memoria.");
        getch();
        exit(EXIT_FAILURE);
    }
    char CharGotten;
    DrawRectangleNoSymbolInside(StartX, StartY);
    gotoxy(StartX + 2, StartY + 1);
    printf("Peticion: ");
    while (true) {
        CharGotten = getch(); // Read a character

        if (CharGotten == 27){
            return NULL;
        }

        if (CharGotten == '\b') { // Handle backspace
            if (LengthOfString > 0) {
                printf("\b \b");
                LengthOfString--;
            }
            continue;
        }

        if (CharGotten == '\r') { 
            StringPetition[LengthOfString] = '\0';
            if (!strcmp(StringPetition, PetitionAutoLarge) || !strcmp(StringPetition, PetitionAutoShort)) {
                break;
            }
            ClearScreen();
            DrawRectangleNoSymbolInside(StartX, StartY);
            gotoxy((Width / 2) - 6, Height / 2);
            printf("La peticion dada es incorrecta.");
            getch();
            ClearScreen();
            DrawRectangleNoSymbolInside(StartX, StartY);
            gotoxy(StartX + 2, StartY + 1);
            printf("Peticion: ");
            LengthOfString = 0;
            continue;
        }

        if (CharGotten == '.') { // Handle custom answer input
            char *Answer = (char *) malloc(InitialSize * sizeof(char));
            int LengthOfAns = 0;
            if (Answer == NULL) {
                gotoxy((Width / 2) - 6, Height / 2);
                printf("Error al re alocar la memoria.");
                getch();
                exit(EXIT_FAILURE);
            }
            char CharInput;
            while (true) {
                CharInput = getch();
                if (CharInput == '.' && LengthOfAns > 0) { // End of answer input
                    Answer[LengthOfAns] = '\0';
                    *AnswerToQuestion = Answer;
                    break;
                }
                if (LengthOfAns + 1 >= InitialSize) {
                    InitialSize *= 2;
                    Answer = (char *) realloc(Answer, InitialSize * sizeof(char));
                    if (Answer == NULL) {
                        gotoxy((Width / 2) - 6, Height / 2);
                        printf("Error al re alocar la memoria.");
                        getch();
                        return NULL;
                    }
                }
                if (LengthOfString + 1 >= InitialSize) {
                    InitialSize *= 2; 
                    StringPetition = (char *) realloc(StringPetition, InitialSize * sizeof(char));
                    if (StringPetition == NULL) {
                        gotoxy((Width / 2) - 5, Height / 2);
                        printf("Error al reservar memoria.");
                        getch();
                        return NULL;
                    }
                }

                Answer[LengthOfAns++] = CharInput;
                if (isalnum(CharInput) || CharInput == ' ') {
                    if (LengthOfString < strlen(PetitionAutoLarge)) {
                        putchar(PetitionAutoLarge[LengthOfString]);
                    }
                    StringPetition[LengthOfString++] = PetitionAutoLarge[LengthOfString];
                }
            }
            continue;
        }

        // Store the input character and print it
        if (LengthOfString + 1 >= InitialSize) {
            InitialSize *= 2;
            StringPetition = (char *) realloc(StringPetition, InitialSize * sizeof(char));
            if (StringPetition == NULL) {
                gotoxy((Width / 2) - 5, Height / 2);
                printf("Error al reservar memoria.\n");
                getch();
                return NULL;
            }
        }

        if (isalnum(CharGotten) || CharGotten == ' '){
            StringPetition[LengthOfString++] = CharGotten;
            putchar(CharGotten); // Display character
        }        
    }

    StringPetition[LengthOfString] = '\0';
    return StringPetition;
}

char *GetQuestion(){
    TerminalSize Dimensions = CalculateTerminalSize();

    // Determine the width and height based on the terminal size
    int Width = Dimensions.columns - StartX * 2 - 2; // Adjusting to fit within the terminal
    int Height = Dimensions.rows - StartY * 2 - 2;   // Adjusting to fit within the terminal

    char Ch;
    int Size = 10;
    int Index = 0;
    char *Question = (char *) malloc(Size * sizeof(char));

    if(Question == NULL){
        gotoxy((Width / 2) - 8, Height / 2);
        printf("Error al reservar memoria.");
        getch();
        exit(EXIT_FAILURE);
    }

    DrawRectangleNoSymbolInside(StartX, StartY);
    gotoxy(StartX + 2, StartY + 2);
    printf("Pregunta (cierre '?'): ");

    while(((Ch = getch()) != '?') || Index < 10){

        if (Ch == '\b') { // Handle backspace
            if (Index > 0) {
                printf("\b \b");
                Index--;
            }
            continue;
        }

        if(Index >= Size){
            Size *= 2;
            Question = (char *) realloc(Question, Size * sizeof(char));
            if (Question == NULL) {
                gotoxy((Width / 2) - 8, Height / 2);
                printf("Error al reservar mas memoria.");
                return NULL;
            }
        }

        if(isalnum(Ch) || Ch == ' '){
            Question[Index++] = Ch;
            putchar(Ch); // Display character
        }   
    }

    putchar(Ch);
    Question[Index] = '?';
    Index++;
    Question[Index] = '\0';
    return Question;
}
#endif