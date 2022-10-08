#ifndef PLAYSTATE_H
#define PLAYSTATE_H
#include<random>
#include"BaseState.h"
class Cube;



class PlayState: public BaseState {
    public:
        PlayState();
        ~PlayState();
        void enter();
        void bgrender();
        void update();
        void render();
        void exit();

    private:
        int score, speed;
        Cube *current, *next;
        int timer;
        char cmd;
        bool notupdate;
        int numOfShape[7];
        //int loopCountOfShape;
        random_device rd;
        uniform_int_distribution<int> uni_dist{ 0, 6 };
};

#endif