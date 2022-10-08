#include"StateMachine.h"
#include"States/StartState.h"
#include"States/PlayState.h"
#include"States/GameoverState.h"
#include"States/HighScoreState.h"
#include"States/EndState.h"
#include<string>
using namespace std;

StateMachine::StateMachine(int n):num(n)
{
    list = new BaseState *[num];
    list[0] = new StartState;
    list[1] = new PlayState;
    list[2] = new GameoverState;
    list[3] = new HighScoreState;
    list[4] = new EndState;
    current = 0;
    end = false;
}

void StateMachine::update()
{
    list[current]->update();
}

void StateMachine::render()
{
    list[current]->render();
}

void StateMachine::change(int stateName, string enterParams)
{
    list[current]->exit();
    current = stateName;
    list[current]->enter(enterParams);
    list[current]->bgrender();
}

void StateMachine::change(int stateName)
{
    list[current]->exit();
    current = stateName;
    list[current]->enter();
    list[current]->bgrender();
}

void StateMachine::stop()
{
    end = true;
}

bool StateMachine::exit()
{
    return end;
}

StateMachine::~StateMachine()
{
    for (int i = 0; i < num; i++) {
        delete list[i];
    }
    delete[] list;
}

StateMachine gStateMachine(5);