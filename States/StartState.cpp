#include"StartState.h"
#include"../StateMachine.h"
#include<stdio.h>
#include<conio.h>
#include<windows.h>
extern short SCREEN_HEIGHT;
extern short SCREEN_WIDTH;
extern StateMachine gStateMachine;

void draw(short, short, const char *);

StartState::StartState():BaseState()
{
    choice = 0;
}

void StartState::update()
{
    char c = _getch();
    if (c == 'q') {
        gStateMachine.stop();
        return;
    }
    if (c == ' ') 
        choice = !choice;
    if (choice == 0 && (c == '\r' || c == '\n')) 
        gStateMachine.change(1);
    if (choice == 1 && (c == '\r' || c == '\n'))
        gStateMachine.change(3, "$");
}

void StartState::bgrender()
{
    draw(SCREEN_WIDTH / 2 - 2, SCREEN_HEIGHT / 3, "TETRIS");
    draw(SCREEN_WIDTH / 2 - 5, SCREEN_HEIGHT / 3 + 1, "------------");
    draw(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 3 + 5, "press 'space' to change, 'enter' to choose");
    draw(SCREEN_WIDTH / 2 - 15, SCREEN_HEIGHT / 3 + 7, "press 'q' to quit at any time");
    draw(SCREEN_WIDTH / 2 - 2, SCREEN_HEIGHT / 3 * 2, "Start");
    draw(SCREEN_WIDTH / 2 - 2, SCREEN_HEIGHT / 3 * 2 + 1, "Highscore");
    draw(SCREEN_WIDTH / 2 - 5, SCREEN_HEIGHT / 3 * 2, "=>");
}

void StartState::render()
{
    if (choice == 0) {
        draw(SCREEN_WIDTH / 2 - 5, SCREEN_HEIGHT / 3 * 2 + 1, "  ");
        draw(SCREEN_WIDTH / 2 - 5, SCREEN_HEIGHT / 3 * 2, "=>");
    } else {
        draw(SCREEN_WIDTH / 2 - 5, SCREEN_HEIGHT / 3 * 2, "  ");
        draw(SCREEN_WIDTH / 2 - 5, SCREEN_HEIGHT / 3 * 2 + 1, "=>");
    }
}

void StartState::exit()
{
    system("cls");
}

