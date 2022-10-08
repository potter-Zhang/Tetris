#include"GameoverState.h"
#include"../StateMachine.h"
#include<iostream>
#include<iomanip>
#include<conio.h>
using namespace std;
extern void draw(short, short, const char *);
extern void draw(short x, short y, int num);
extern void draw(short x, short y, string s);
extern short WINDOW_WIDTH;
extern short WINDOW_HEIGHT;
extern short SCREEN_WIDTH;
extern short SCREEN_HEIGHT;
extern StateMachine gStateMachine;

void GameoverState::enter(string enterParams)
{
    score = stoi(enterParams);
    draw(SCREEN_WIDTH / 2 - 3, SCREEN_HEIGHT / 3, "YOU LOST");
    draw(SCREEN_WIDTH / 2 - 5, SCREEN_HEIGHT / 3 + 5, "YOUR SCORE: ");
    draw(SCREEN_WIDTH / 2 + 7, SCREEN_HEIGHT / 3 + 5, score);
    draw(SCREEN_WIDTH / 2 - 15, SCREEN_HEIGHT / 2 + 5, "please enter your name: ");
    cin >> setw(12) >> name;
    system("cls");
}

void GameoverState::bgrender()
{
    if (score <= 30) {
        draw(SCREEN_WIDTH / 2 - 7, SCREEN_HEIGHT / 3, "--- Novice ---");
    } else if (score <= 100) {
        draw(SCREEN_WIDTH / 2 - 7, SCREEN_HEIGHT / 3, "--- Hotshot ---");
    } else if (score <= 180) {
        draw(SCREEN_WIDTH / 2 - 7, SCREEN_HEIGHT / 3, "--- Phenom ---");
    } else {
        draw(SCREEN_WIDTH / 2 - 7, SCREEN_HEIGHT / 3, "--- Master ---");
    }
    draw(SCREEN_WIDTH / 2 - 7, SCREEN_HEIGHT / 3 + 7, "SCORE: ");
    draw(SCREEN_WIDTH / 2 + 5, SCREEN_HEIGHT / 3 + 7, score);
    draw(SCREEN_WIDTH / 2 - 7, SCREEN_HEIGHT / 2 + 5, "NAME: ");
    draw(SCREEN_WIDTH / 2 + 2, SCREEN_HEIGHT / 2 + 5, name);
    draw(SCREEN_WIDTH / 2 - 13, SCREEN_HEIGHT / 2 + 7, "press 'enter' to continue");

}

void GameoverState::update()
{
    if (_kbhit()) {
        char c = _getch();
        if (c == '\r' || c == '\n') {
            gStateMachine.change(3, name + "&" + to_string(score));
        }
        if (c == 'q') {
            gStateMachine.stop();
            return;
        }
    }
}

void GameoverState::exit()
{
    system("cls");
}