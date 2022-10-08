#include<iostream>
#include"BaseState.h"


class GameoverState: public BaseState {
    public:
        void enter(string enterParams);
        void bgrender();
        void update();
        void exit();

    private:
        int score;
        string name;
        //bool kbhit;
};