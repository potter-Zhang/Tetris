#include"EndState.h"
#include<windows.h>
#include<stdio.h>
extern void setColor(int color);
extern void draw(short, short, const char *);
extern void gotoxy(short, short);
extern short SCREEN_HEIGHT;
extern short SCREEN_WIDTH;

void EndState::bgrender()
{
    setColor(15);
    draw(SCREEN_WIDTH / 2 - 8, SCREEN_HEIGHT / 3, "====== Bye ======");
    draw(SCREEN_WIDTH / 2 - 8, SCREEN_HEIGHT / 3 + 4, "-----------------");
    draw(SCREEN_WIDTH / 2 - 6, SCREEN_HEIGHT / 3 + 5, "Little Prince");
    draw(SCREEN_WIDTH / 2 - 8, SCREEN_HEIGHT / 3 + 6, "-----------------");
    draw(SCREEN_WIDTH / 2 - 17, SCREEN_HEIGHT / 3 + 20, "window will be closed in ");
    draw(SCREEN_WIDTH / 2 + 12, SCREEN_HEIGHT / 3 + 20, "seconds.");
}
void EndState::render()
{
    gotoxy(SCREEN_WIDTH / 2 + 9, SCREEN_HEIGHT / 3 + 20);
    for (int i = 3; i > 0; i--) {
        printf("%d", i);
        Sleep(1000);
        printf("\b");
    }
    //system("cls");
}