#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

char board[] = {'_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_',
                '_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_',
                '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
                ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
                ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
                ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
                ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
                ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
                ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                '_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_',
                '_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_',
               };

int value=2;
int sum = 0, count=0;
int hor=2, vert=1, test=167, last=0, head=3, points=0;
bool stop=false;
int countH=2, countV=1;
int collide=0;
vector<int>headV;

void display();
void change();
void ifPress();
void getLast();
void getFood();
void checkLoss();
void run(int speed);
void getKey(int key);

int main()
{
    int input;
    while (true)
    {
        cout << "Choose level" << endl;
        cout << "1. Easy"<< endl;
        cout << "2. Normal" << endl;
        cout << "3. Hard" << endl;
        cout << "4. Extreme" << endl;
        cout << "--> " << flush;
        cin >> input;

        if (input==1)
        {
            run(300);
            break;
        }
        else if (input==2)
        {
            run(100);
            break;
        }
        else if (input==3)
        {
            run(40);
            break;
        }
        else if (input==4)
        {
            run(0);
            break;
        }
        else
        {
            system("cls");
            cout << "Invalid Speed, try again." << endl;
        }
    }
    Sleep(4000);
    return 0;
}

void run(int speed)
{
    cout << "Press right key to start" << endl;
    display();
    while (true)
    {
        if (kbhit())
        {
            break;
        }
    }
    while(stop==false)
    {
        display();
        if (kbhit())
        {
            ifPress();
        }
        else
        {
            getLast();
        }
        getFood();

        change();

        system("cls");

        checkLoss();

        display();

        Sleep(speed);
    }
}



void display()
{
    int countBoard=0;
    for (int i=0; i<320; i++)
    {
        cout << board[i] << flush;
        countBoard++;
        if (countBoard==40 | countBoard==80 | countBoard==120 | countBoard==160 |
                countBoard==200 | countBoard==240 | countBoard==280 | countBoard==320)
        {
            cout << endl;
        }

    }

}

void change()
{
    if(sum!=0)
    {
        board[sum] = 'o';
    }
    sum = hor * 40;
    sum = sum + vert;

    if (board[sum] == 'o')
    {
        collide=1;
    }

    board[test] = '*';
    board[sum] = 'O';

    headV.push_back(sum);

    if(countV==vert+1)
    {
        last=2;
        countV--;
    }
    else if(countV==vert-1)
    {
        last=1;
        countV++;
    }
    else if(countH==hor+1)
    {
        last=4;
        countH--;
    }
    else if(countH==hor-1)
    {
        last=3;
        countH++;
    }

    if (headV.size() >= 3)
    {
        int comp = headV.size() - head;

        board[headV[comp]] = ' ';
    }
}

void ifPress()
{
    const int KEY_ARROW_CHAR1 = 224;
    const int KEY_ARROW_UP = 72;
    const int KEY_ARROW_DOWN = 80;
    const int KEY_ARROW_LEFT = 75;
    const int KEY_ARROW_RIGHT = 77;
    int key;

    unsigned char ch1 = _getch();
    if (ch1 == KEY_ARROW_CHAR1)
    {
        unsigned char ch2 = _getch();
        switch (ch2)
        {
        case KEY_ARROW_UP:
            hor--;
            break;
        case KEY_ARROW_DOWN:
            hor++;
            break;
        case KEY_ARROW_LEFT:
            vert--;
            break;
        case KEY_ARROW_RIGHT:
            vert++;
            break;
        }
    }

}

void getLast ()
{
    if(last == 1)
    {
        vert++;
    }
    else if(last == 2)
    {
        vert--;;
    }
    else if(last == 3)
    {
        hor++;
    }
    else if(last == 4)
    {
        hor--;
    }
}

void getFood()
{

    srand(time(0));
    if (test==sum)
    {
        while (true)
        {
            test = (rand()%240) + 40;
            if (board[test] == ' ')
            {
                break;
            }
        }
        head++;
        points++;
    }

}

void checkLoss()
{
    if (collide == 1 | vert==39 | vert==0 | hor == 0 | hor ==7)
    {
        stop = true;
        cout << "Points = " << points << endl;
        cout << "              GAME OVER"<< endl;
    }
}

