#include"PlayState.h"
#include"../Cube.h"
#include"../Map.h"
#include"../StateMachine.h"
#include<windows.h>
#include<stdio.h>
#include<conio.h>
extern void draw(short, short, const char *);
extern void draw(short x, short y, int num);
extern void draw(short, short, const char *, int);
extern void setColor(int);
extern short WINDOW_WIDTH;
extern short WINDOW_HEIGHT;
extern short SCREEN_WIDTH;
extern short SCREEN_HEIGHT;
struct cubeshape {
    short x[4]; 
    short y[4];
};
extern struct cubeshape shapesheet[7][4];
extern Map gMap;
extern StateMachine gStateMachine;

PlayState::PlayState():BaseState()
{
    memset(numOfShape, 0, sizeof(numOfShape));
    //loopCountOfShape = 0;
    speed = 200;
    score = 0;
    current = new Cube();
    next = new Cube();
    timer = 0;
    cmd = 'c';
    notupdate = false;
    
    next->setXY(SCREEN_WIDTH / 2 - 2, SCREEN_HEIGHT - 25);
}

void PlayState::enter()
{
    memset(numOfShape, 0, sizeof(numOfShape));
    notupdate = false;
    //loopCountOfShape = 0;
    speed = 200;
    score = 0;
    int randShape;
    current->generateCube(randShape = uni_dist(rd));
    numOfShape[randShape]++;
    next->generateCube(randShape = uni_dist(rd));
    numOfShape[randShape]++;
    next->setXY(SCREEN_WIDTH / 2 - 2, SCREEN_HEIGHT - 25);
    gMap.reset();
}

void PlayState::update()
{
    cmd = 'c';
    bool kbhit;
    if (kbhit = _kbhit()) {
        cmd = _getch();
        if (cmd == 'q') {
            gStateMachine.stop();
            return;
        }
        if (cmd == ' ') {
            //pause = !pause;
            draw(SCREEN_WIDTH / 4 + 9, SCREEN_HEIGHT / 4 - 8, "==> PAUSE <==");
            while ((cmd = _getch()) != ' ' && cmd != 'q');
            if (cmd == 'q') {
                gStateMachine.stop();
                return;
            }
            //pause = !pause;
            draw(SCREEN_WIDTH / 4 + 9, SCREEN_HEIGHT / 4 - 8, "             ");
        } //else if (cmd == 'p')
            //score += 100;    
    }
    
    notupdate = current->update(cmd, kbhit, timer == 5);
    
    if (current->getEnd()) {
        current->setEnd(false);
        current->setSpeed(false);
        if (!gMap.addCube(*current)) {
            gStateMachine.change(2, to_string(score));
            return;
        }
        int numLine = gMap.deleteLine();
        if (numLine > 1) {
            score += (numLine - 1) * 15 + 10;
        } else if (numLine == 1) {
            score += 10;
        }
        gMap.render();
        bgrender();
        Cube *tmp = current;
        current = next;
        current->erase();
        current->setXY(WINDOW_WIDTH / 2 - 2, 3);
        next = tmp;
        int randShape = uni_dist(rd);
        numOfShape[randShape]++;
        next->generateCube(randShape);
        next->setXY(SCREEN_WIDTH / 2 - 2, SCREEN_HEIGHT - 25);
        next->render();
        //loopCountOfShape++;
    }
    if (current->getSpeed()) {
        speed = 0;
    } else {
        speed = 20;
    }
    if (timer++ > 5)
        timer = 0;
    Sleep(speed);
}

void PlayState::bgrender()
{
    draw(20 + SCREEN_WIDTH / 2 - 4, SCREEN_HEIGHT - 25 - 3, "NEXT ONE", 15);
    draw(SCREEN_WIDTH / 4 - 10, SCREEN_HEIGHT - 25 - 3, "YOUR SCORE : ");
    for (short i = 4; i < WINDOW_HEIGHT; i++) {
        draw(19, i, "|");
        draw(40, i, "|");
    }
    draw(20, 30, "--------------------");
    setColor(15);
    draw(SCREEN_WIDTH / 4 - 6, SCREEN_HEIGHT - 25 , score);
    draw(SCREEN_WIDTH / 4 + 5, 2, "                    ");
    draw(SCREEN_WIDTH / 4 + 5, 3, "--------------------");
    draw(14, 32, "a = move left, d = move right");
    draw(15, 33, "s = move down, space = pause");
    draw(22, 34, "j or k = spin");
    
    next->render();
}

void PlayState::render()
{
    //if (pause)
        //return;
    //cubes rendering
    if (!notupdate)
        current->render();
    

    //background infomation
    setColor(15);
    draw(SCREEN_WIDTH / 4 - 6, SCREEN_HEIGHT - 25 , score);
    draw(SCREEN_WIDTH / 4 + 5, 2, "                    ");
    draw(SCREEN_WIDTH / 4 + 5, 3, "--------------------");
    
}

void PlayState::exit()
{
    system("cls");
}

PlayState::~PlayState()
{
    delete current;
    delete next;
}

