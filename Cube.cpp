#include"Cube.h"
#include"Map.h"
#include"StateMachine.h"
#include<iostream>
#include<conio.h>
using namespace std;
extern short WINDOW_WIDTH;
extern short WINDOW_HEIGHT;
struct cubeshape {
    short x[4]; 
    short y[4];
};
extern struct cubeshape shapesheet[2][4];
extern void draw(short x, short y, const char *str, int color);
extern void draw(short x, short y, const char *str);
extern Map gMap;
extern StateMachine gStateMachine;
extern void setColor(int);

void Cube::generateCube(int shape)
{
    this->shape = (type)shape;
    color = rand() % 7;
    speed = end = false;

    if (shape == I || shape == O)
        X = x = WINDOW_WIDTH / 2 - 2;
    else 
        X = x = WINDOW_WIDTH / 4;
    
    if (X & 1) {
        X = ++x;
    }

    Rotation = rotation = 0;
    Y = y = 3;

    cmd = 'c';
    //return shape;
}

Cube::Cube()
{
    xbias = 20;
    ybias = 0;
    generateCube(0);
}

void Cube::setxy(short x, short y)
{
    this->x = x;
    this->y = y;
}

void Cube::setXY(short X, short Y)
{
    this->X = this->x = X;
    this->Y = this->y = Y;
}

bool Cube::collides()
{
    for (int i = 0; i < 4; i++) {
        //boundary check
        short X = x + shapesheet[shape][rotation].x[i];
        short Y = y + shapesheet[shape][rotation].y[i];
        if (X < 0 || Y < 0 || X >= WINDOW_WIDTH || Y >= WINDOW_HEIGHT)
            return true;
        if (gMap.getMap(X, Y))
            return true;
    }
    return false;

}

void Cube::move()
{
    //keep old values
    //X = x;

    //move left
    if (cmd == 'a')
        x -= 2;
    //move right
    else if (cmd == 'd')
        x += 2;
    //move down
    else if (cmd == 's')
        speed = true;
    
        
    if (collides())
        x = X;

    
}

void Cube::fall()
{
    //move down
    //Y = y;
    y++;
    if (collides()) {
        y = Y;
        end = true;
    }
}

void Cube::spin()
{
    //get player's input and keep old values
    //Rotation = rotation;

    //left turn
    if (cmd == 'j') {
        rotation = (rotation - 1 + 4) % 4;
        if (collides()) {
            rotation = Rotation;
        }
    }

    //right turn
    if (cmd == 'k') {
        rotation = (rotation + 1) % 4;
        if (collides()) {
            rotation = Rotation;
        }
    }

    //fall();
}

bool Cube::update(char c, bool kbhit, bool down)
{
    if (end)
        return 1;
    cmd = c;
    if(kbhit) {   
        move();
        spin();
    } 
    if (down) {
        fall();
    }
    return kbhit || down;
       
}

void Cube::erase()
{
    for (int i = 0; i < 4; i++) {
            draw(X + shapesheet[shape][Rotation].x[i] + xbias, Y + shapesheet[shape][Rotation].y[i] + ybias, "  ");
        }
}

void Cube::render()
{
    if (!end) {
        for (int i = 0; i < 4; i++) 
            draw(X + shapesheet[shape][Rotation].x[i] + xbias, Y + shapesheet[shape][Rotation].y[i] + ybias, "  ");
        //reset
        Rotation = rotation;
        X = x;
        Y = y;
        setColor(color + 9);
        for (int i = 0; i < 4; i++) 
            draw(x + shapesheet[shape][rotation].x[i] + xbias, y + shapesheet[shape][rotation].y[i] + ybias, "¡ö");
        
    } 
}

//get function
short Cube::getShape()
{
    return shape;
}

int Cube::getColor()
{
    return color;
}

short Cube::getRot()
{
    return rotation;
}

short Cube::getX()
{
    return x;
}

short Cube::getY()
{
    return y;
}

bool Cube::getEnd()
{
    return end;
}

bool Cube::getSpeed()
{
    return speed;
}

//set function
void Cube::setEnd(bool end)
{
    this->end = end;
}

void Cube::setSpeed(bool speed)
{
    this->speed = speed;
}

char Cube::cmd = 'c';