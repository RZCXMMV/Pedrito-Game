
#ifndef MENU_H
#define MENU_H

void MoveTroughMainMenu(void);
void DisplayMainMenu(int Option);

#endif

#ifndef FUNCTIONPROTOTYPES_H
#define FUNCTIONPROTOTYPES_H

int StoreHistoryDataInFile(char *Question, char *Response);
int ViewHistoryDataInFile();
void GetGameInstructions();
void PlayGame();

#endif