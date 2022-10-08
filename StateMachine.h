#include"states/BaseState.h"

class StateMachine {
    public:
        StateMachine(int n);
        ~StateMachine();
        void change(int stateName, string enterParams);
        void change(int stateName);
        void update();
        void render();
        void stop();
        bool exit();

    private:
        int num;
        int current;
        BaseState **list;
        bool end;
};