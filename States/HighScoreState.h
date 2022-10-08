#ifndef HIGHSCORESTATE_H
#define HIGHSCORESTATE_H

#include<iostream>
#include<map>
#include<algorithm>
#include<vector>
#include"BaseState.h"
using namespace std;

class HighScoreState: public BaseState{
    public:
        HighScoreState();
        void enter(string enterParams);
        void update();
        void bgrender();
        //void render();
        void exit();
    
    private:
        static const int num = 10;
        map<string, int> list;
        vector<pair<string, int>> printList;
};

#endif