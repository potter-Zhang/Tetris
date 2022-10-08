#include<conio.h>
#include<windows.h>
#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;

void gotoxy(short x, short y)
{
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void draw(short x, short y, const char *str, int color)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {x, y};
    SetConsoleCursorPosition(h, coord);
    SetConsoleTextAttribute(h, color);
    //printf("%s", str);
    cout << str;

}

void draw(short x, short y, const char *str)
{
    gotoxy(x, y);
    //printf("%s", str);
    cout << str;
}

void draw(short x, short y, int num)
{
    gotoxy(x, y);
    printf("%d", num);
}

void draw(short x, short y, string s)
{
    gotoxy(x, y);
    cout << s;
}

void hideCursor()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(handle, &CursorInfo);
}

void fixWindow()
{
    HWND hWnd = GetConsoleWindow(); 
    RECT rc;
    GetWindowRect(hWnd, &rc); 
 
    
    SetWindowLongPtr(hWnd, 
        GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
    
    SetWindowPos(hWnd,
        NULL,
        rc.left,
        rc.top,
        rc.right - rc.left, rc.bottom - rc.top,
        0);
}

