#include"StateMachine.h"
#include<iostream>
#include<windows.h>
#include<ctime>
#include<conio.h>
using namespace std;
extern StateMachine gStateMachine;
extern short WINDOW_HEIGHT;
extern short WINDOW_WIDTH;

void hideCursor();
void load();
void unload();
void fixWindow();

int main()
{  
    load();
    while (true) {
        gStateMachine.update();
        gStateMachine.render();
        if (gStateMachine.exit())
            break;
    }
    unload();
}

void load()
{
    srand(time(0));
    system("mode con cols=60 lines=40");
    hideCursor();
    fixWindow();
    gStateMachine.change(0);
}

void unload()
{
    gStateMachine.change(4);
    gStateMachine.render();
    system("cls");
    //system("pause");
}

