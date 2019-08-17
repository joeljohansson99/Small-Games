#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
//MAP
void initMap();
void display();
vector<char>board;
bool stop=false;
string win;
//RACKETS
void playerOneMove(char key);
void playerTwoMove(char key);
int oneMove=6, twoMove=5, oneLast=6, twoLast=5;
void moveRackets();

//BALL
void getBall();
void ballHit();
int xBall=20, yBall=5, direct=rand()%4+1;

int main()
{
    initMap();
    while (stop==false)
    {
        if(kbhit())
        {
            char ch=getch();
            if(ch=='w' | ch=='s')
            {
                playerTwoMove(ch);
            } else if (ch=='o' | ch=='k') {
                playerOneMove(ch);
            }

        }
        moveRackets();
        getBall();
        Sleep(200);
        system("cls");
        display();
    }
    cout << endl << "    " << win << " wins!" << endl;
    Sleep(4000);

    return 0;
}

void getBall() {
    board[yBall*40+xBall] = ' ';
    ballHit();
    if (direct==1) {
        xBall++;
        yBall--;
        if (yBall == 1) {direct=2;}
    }
    else if (direct==2) {
        xBall++;
        yBall++;
        if (yBall == 8) {direct=1;}
    }
    else if (direct==3) {
        xBall--;
        yBall++;
        if (yBall == 8) {direct=4;}
    }
    else if (direct==4) {
        xBall--;
        yBall--;
        if (yBall == 1) {direct=3;}
    }
    board[yBall*40+xBall] = 'o';
}
void ballHit() {
    srand(time(0));
    if (yBall==oneMove-1 && xBall==38) {
        direct=3;
    }
    else if (yBall==twoMove && xBall==1) {
        direct=rand()%2+1;
    }
    if (xBall==39)
    {
        stop=true;
        win = "Player one";
    }
    if (xBall==0) {
        stop=true;
        win = "Player two";
    }

}

void moveRackets() {
    board[twoLast*40] = ' ';
    board[oneLast*40-1] = ' ';
    if (twoMove==1) {twoMove++;}
    if (twoMove==10) {twoMove--;}
    if (oneMove==1) {oneMove++;}
    if (oneMove==10) {oneMove--;}
    board[twoMove*40] = '|';
    board[oneMove*40-1] = '|';
    oneLast=oneMove;
    twoLast=twoMove;
}


void playerOneMove(char key)
{
    switch (key)
    {
    case 'o':
        oneMove--;
        break;
    case 'k':
        oneMove++;
        break;
    }
}

void playerTwoMove(char key)
{
    switch (key)
    {
    case 'w':
        twoMove--;
        break;
    case 's':
        twoMove++;
        break;
    }
}

//MAP
void initMap()
{
    for (int i=0; i<400; i++)
    {
        if (i<40) {board.push_back('_');}
        else if (i>360) {board.push_back('_');}
        else {board.push_back(' ');}


    }
}

void display()
{
    for (int n=0; n<board.size(); n++)
    {
        cout << board[n] << flush;
        if (n==39 | n==79 | n==119 | n==159 | n==199 | n==239 | n==279 | n==319 | n==359)
        {
            cout << endl;
        }
    }
}
