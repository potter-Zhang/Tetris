#include<fstream>
#include<conio.h>
#include<algorithm>
#include"HighScoreState.h"
#include"../StateMachine.h"
extern StateMachine gStateMachine;
extern void draw(short, short, const char *);
extern void draw(short x, short y, int num);
extern void draw(short, short, const char *, int);
void draw(short x, short y, string s);
extern short WINDOW_WIDTH;
extern short WINDOW_HEIGHT;
extern short SCREEN_WIDTH;
extern short SCREEN_HEIGHT;

bool cmp(pair<string, int> a, pair<string, int> b)
{
    return a.second == b.second ? a.first < b.first : a.second > b.second;
}

HighScoreState::HighScoreState()
{
    fstream file;
    file.open("./highscore.lst", ios_base::in);
    if (!file)
        return;

    string name;
    int score;
    //char test;
     for (int i = 0; i < 10; i++) {
        file >> name;
        file >> score;
        if (file.eof())
            break;
        list.insert(make_pair(name, score));
        printList.push_back(make_pair(name, score)); 
    }
    sort(printList.begin(), printList.end(), cmp);
    file.close();
}

void HighScoreState::enter(string enterParams)
{
    if (enterParams == "$")
        return;

        bool changed = true;

        auto splitIndex = enterParams.find_first_of('&');
        string name = enterParams.substr(0, splitIndex);
        int score = stoi(enterParams.substr(splitIndex + 1));
        
        pair<string, int> tmp = {name, score};
        if (printList.size() < 10) {
            if (list.find(name) == list.end()) {
                list.insert(tmp);
                printList.push_back(tmp);
                sort(printList.begin(), printList.end(), cmp);
            } else if (list[name] < score) {
                pair<string, int> tmp = {name, list[name]};
                auto it = find(printList.begin(), printList.end(), tmp);
                it->second = score;
                list[name] = score;
                sort(printList.begin(), printList.end(), cmp);
            } else {
                changed = false;
            }
        } else {
            if (list.find(name) == list.end()) {
                printList.push_back(tmp);
                sort(printList.begin(), printList.end(), cmp);
                list.insert(tmp);
                list.erase((printList.end() - 1)->first);
                printList.pop_back();
            } else if (list[name] < score) {
                pair<string, int> tmp = {name, list[name]};
                auto it = find(printList.begin(), printList.end(), tmp);
                it->second = score;
                list[name] = score;
                sort(printList.begin(), printList.end(), cmp);
            } else {
                changed = false;
            }
        }
        
        if (!changed)
            return;
        fstream file;
        file.open("./highscore.lst", ios_base::out);
        for (auto it = list.begin(); it != list.end(); ++it) {
            file << it->first << endl;
            file << it->second << endl;
        }
        file.close();
}

void HighScoreState::bgrender()
{
    draw(SCREEN_WIDTH / 2 - 3, SCREEN_HEIGHT / 4, "TOP 10", 15);
    draw(SCREEN_WIDTH / 2 - 13, SCREEN_HEIGHT / 4 + 1, "**************************");
    draw(SCREEN_WIDTH / 2 - 13, SCREEN_HEIGHT / 4 + 2, "RANK       NAME      SCORE");

    int i = 1;
    for (auto it = printList.begin(); it != printList.end(); i++, it++) {
        draw(SCREEN_WIDTH / 2 - 12, SCREEN_HEIGHT / 4 + 4 + i, i);
        draw(SCREEN_WIDTH / 2 - 5, SCREEN_HEIGHT / 4 + 4 + i, it->first);
        draw(SCREEN_WIDTH / 2 + 9, SCREEN_HEIGHT / 4 + 4 + i, it->second);
    }
    draw(SCREEN_WIDTH / 2 - 12, SCREEN_HEIGHT / 4 + 4 + 12, "press 'enter' to continue");
}

void HighScoreState::update()
{
    if (_kbhit()) {
        char c = _getch();
        if (c == '\r' || c == '\n')
            gStateMachine.change(0);
        if (c == 'q')
            gStateMachine.stop();
    }
}

void HighScoreState::exit()
{

    system("cls");
}

