#include"BaseState.h"

class StartState: public BaseState {
    public:
        StartState();
        virtual void update();
        virtual void bgrender();
        virtual void render();
        virtual void exit();

    private:
        int choice;
};