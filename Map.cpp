#include"Map.h"
#include<iostream>
using namespace std;
struct cubeshape {
    short x[4]; 
    short y[4];
};
extern struct cubeshape shapesheet[2][4];
extern void draw(short, short, const char *);
extern void draw(short, short, int);
extern void draw(short, short, const char *, int);
extern short WINDOW_WIDTH;
extern short WINDOW_HEIGHT;

int max(int a, int b)
{
    return a > b ? a : b;
}

//map[y][x]
Map::Map(short w, short h):w(w), h(h)
{
    //new a map
    map = new mapblocks *[h];
    for (short i = 0; i < h; i++) {
        map[i] = new mapblocks[w];
        for (short j = 0; j < w; j++) {
            map[i][j].block = false;
        }
    }

    line = new bool[h]{false};
    xbias = 20;
    ybias = 0;
    maxh = 0;
}

bool Map::checkLine(short lineNum)
{
    for (int i = 0; i < w; i++) {
        if (!map[lineNum][i].block)
            return false;
    }
    return true;
}

void Map::moveDown()
{
    int drop = 0;
    for (short i = 0; i < maxh; i++) {
        if (line[i]) {
            drop++;
            line[i] = false;
            continue;
        }
        if (drop != 0) {
            for (int j = 0; j < w; j++) {
                map[i - drop][j] = map[i][j];
                map[i][j].block = false;
            }
        }

    }
    
    maxh -= drop;
}

int Map::deleteLine()
{
    int cnt = 0;
    for (short i = 0; i < maxh; i++) {
        if (checkLine(i)) {
            for (short j = 0; j < w; j++) {
                map[i][j].block = false;
            }
            line[i] = true;
            cnt++;
        }
    }
    
    moveDown();
    return cnt;
}

void Map::render()
{
    //erase
    system("cls");

    //print the map
    for (short i = 0; i < maxh; i++) {
        for (short j = 0; j < w; j++) {
            if (map[i][j].block)
                draw(xbias + 2 * j, ybias + h - i - 1, "¡ö", map[i][j].color + 9);
        }
    }

    //for debug
    //draw(0, 0, "maxh = ");
    //draw(5, 0, maxh);
    

}

bool Map::addCube(Cube &c)
{
    for (int i = 0; i < 4; i++) {
        short ix = h - (c.y + shapesheet[c.shape][c.rotation].y[i]) - 1;
        short iy = (c.x + shapesheet[c.shape][c.rotation].x[i]) / 2;
        map[ix][iy].block = true;
        map[ix][iy].color = c.color;
        ix++;
        maxh = max(maxh, ix);
    }
    if (maxh >= WINDOW_HEIGHT - 2)
        return false;
    return true;
}

//get fucntion
bool Map::getMap(short x, short y)
{
    return map[h - y - 1][x / 2].block;
}

void Map::reset()
{
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            map[i][j].block = false;
        }
    }
    maxh = 0;
}

Map::~Map()
{
    for (short i = 0; i < h; i++) 
        delete[] map[i];
    delete[] map;
}

Map gMap(WINDOW_WIDTH / 2, WINDOW_HEIGHT);