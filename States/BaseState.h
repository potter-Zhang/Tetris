#ifndef BASESTATE_H
#define BASESTATE_H
#include<string>
using namespace std;

class BaseState {
    public:
        BaseState();
        virtual ~BaseState();
        virtual void enter(string enterParams);
        virtual void enter();
        virtual void exit();
        virtual void update();
        virtual void bgrender();
        virtual void render();
};
#endif