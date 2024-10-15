#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>


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
    char *PetitionAutoLarge = "Pedro por favor responde esta pregunta";
    char *PetitionAutoShort = "Pedro por favor responde";
    int InitialSize = 10;
    int LengthOfString = 0;
    char *StringPetition = (char *) malloc(InitialSize * sizeof(char));
    if (StringPetition == NULL) {
        printf("Error al reservar memoria.\n");
        getch();
        exit(EXIT_FAILURE);
    }
    char CharGotten;

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
            printf("\nLa peticion dada es incorrecta.\n");
            getch();
            ClearScreen();
            printf("Peticion: ");
            LengthOfString = 0;
            continue;
        }

        if (CharGotten == '.') { // Handle custom answer input
            char *Answer = (char *) malloc(InitialSize * sizeof(char));
            int LengthOfAns = 0;
            if (Answer == NULL) {
                printf("Error al re alocar la memoria.\n");
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
                        printf("Error al re alocar la memoria.\n");
                        getch();
                        return NULL;
                    }
                }
                if (LengthOfString + 1 >= InitialSize) {
                    InitialSize *= 2; 
                    StringPetition = (char *) realloc(StringPetition, InitialSize * sizeof(char));
                    if (StringPetition == NULL) {
                        printf("Error al reservar memoria.\n");
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

    char Ch;
    int Size = 10;
    int Index = 0;
    char *Question = (char *) malloc(Size * sizeof(char));

    if(Question == NULL){
        printf("Error al reservar memoria.\n");
        getch();
        exit(EXIT_FAILURE);
    }

    printf("\nPregunta (cierre '?'): ");

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
                printf("Error al reservar mas memora.\n");
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