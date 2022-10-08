#ifndef MAP_H
#define MAP_H

#include"Cube.h"
#include<vector>
typedef struct blocks {
    bool block;
    int color;
} mapblocks;
class Map {
    public:
        Map(short w, short h);
        ~Map();
        bool checkLine(short lineNum);
        int deleteLine();
        void moveDown();
        void render();
        bool addCube(Cube &);
        void reset();

        //get function
        bool getMap(short x, short y);

    private:
        short w, h;
        short xbias, ybias;
        short maxh;
        mapblocks **map;
        bool *line;
};
#endif