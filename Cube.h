#ifndef CUBE_H
#define CUBE_H
class Map;

class Cube {
    public: 
        Cube();
        void move();
        void spin();
        void fall();
        bool collides();
        bool update(char c, bool kbhit, bool down);
        void render();
        void setxy(short x, short y);
        void setXY(short X, short Y);
        void generateCube(int shape);
        void erase();

        //get function
        short getShape();
        int getColor();
        short getRot();
        short getX();
        short getY();
        bool getEnd();
        bool getSpeed();

        //set function
        void setSpeed(bool);
        void setEnd(bool);
        
        friend Map;
    
    private:
        bool end;
        bool speed;
        enum type { I, J, L, O, S, T, Z };
        short x, y, X, Y;
        short xbias, ybias;
        type shape;
        int color;
        int rotation, Rotation;
        static char cmd;
};

#endif