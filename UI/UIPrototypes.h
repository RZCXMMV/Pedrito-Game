#include "UIStructs.h"

#ifndef UIPROTOTYPES_H
#define UIPROTOTYPES_H

TerminalSize CalculateTerminalSize(void);
void gotoxy(int, int);
void LoadLoadingBar(char *);
void LoadLogoUni(void);
void DrawRectangle(int, int, int, int, float, const char *);
void DrawRectangleNoSymbolInside(int, int);
bool noKeyPressed(void);
void ShowCredentials(void);

#endif