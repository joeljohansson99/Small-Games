#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <vector>
using namespace std;

vector<char>playground;
vector<int>shots;

class Ship {
public:
    Ship(){for (int i=0; i<15*20; i++){playground.push_back(' ');}};
    void ship_position();
    void ship_move();
    void shot_position();
    void display();
    void get_shot(int shot);
    void update_map();
    void get_shots_left();
    void get_shots_right();
    int points=0;
    int move=5;
    bool stop=true;
private:
    int fade=0;
    int shot;
};

vector<int>ghosts;


class Ghost {
public:
    Ghost(){};
    void get_ghost(int clock);
    void move_ghost();
    bool stop = true;
private:
    int clock;
    int random;

};

vector<int>killers;
vector<int>powers;

class Killer {
public:
    void get_killer();
    void move_killer();
    void get_power();
    bool stop = true;
    void level();
private:
    int timer;
    int count_killer=15;
    int power;
    int level_chose;
};


int main()
{

    int count = 0;
    Ship ship;
    Ghost ghost;
    Killer killer;
    killer.level();
    while(ghost.stop==true && killer.stop==true && ship.stop==true) {
        if (kbhit()){
        ship.ship_move();
        }
        ship.ship_position();
        if (count%25==0 | count==1){
            killer.get_killer();
            killer.move_killer();
        }

        if (count%2==0){killer.get_power();}
        if (count%25==0 | count==0){
            ghost.get_ghost(1);
            ghost.move_ghost();
        }
        ship.update_map();

        Sleep(0);
        system("cls");
        ship.display();
        count++;
    }
    cout << "Game Over" << endl;
    cout <<"You got "<< ship.points << " points!" <<endl;
    return 0;
}

void Killer::level() {
    cout << "Choose level." << endl;
    cout << "1.Extreme" << endl;
    cout << "2.Hard" << endl;
    cout << "3.Normal" << endl;
    cout << "4.Easy" << endl;
    cin >> level_chose;
}

void Killer::get_killer() {
    if (count_killer==level_chose-1) {
        count_killer++;
    }
    srand(time(0));
    timer=rand()%count_killer + 1;
    if (timer==1) {
        timer = rand()%15;
        killers.push_back(timer);
    }
    count_killer--;
}

void Killer::move_killer() {
    for (int k=0; k<killers.size(); k++) {
        playground[killers[k]] = ' ';
        killers[k]=killers[k]+15;
        playground[killers[k]] = 'V';
        srand(time(0));
        power = rand()%3;
        if (power == 2) {
            powers.push_back(killers[k]);
        }
        if (killers[k]>284) {
            stop=false;
        }
    }

}

void Killer::get_power(){
    for (int k=0; k<powers.size(); k++) {
        if (powers[k]!= 'V'){playground[powers[k]] = ' ';}
        powers[k]=powers[k]+15;
        playground[powers[k]] = '|';

        if (powers[k]>300) {
            powers.erase(powers.begin()+k);
        }
    }
}

void Ghost::move_ghost() {
    for (int s=0; s<ghosts.size(); s++) {
        playground[ghosts[s]] = ' ';
        ghosts[s]=ghosts[s]+15;
        playground[ghosts[s]] = 'o';
        if (ghosts[s]>284) {
            stop=false;
        }
    }
}

void Ship::update_map() {
    for (int u=0; u<shots.size(); u++) {
        for (int y=0; y<ghosts.size(); y++){
            if (shots[u]==ghosts[y]) {
                    points++;
                    playground[shots[u]] = ' ';
                    ghosts.erase(ghosts.begin()+y);
                    shots.erase(shots.begin()+u);

            }
        }
    }
    for (int q=0; q<shots.size(); q++) {
        for (int r=0; r<killers.size(); r++){
            if (shots[q]==killers[r]) {
                    points+=4;
                    playground[shots[q]] = ' ';
                    killers.erase(killers.begin()+r);
                    shots.erase(shots.begin()+q);

            }
        }
    }
    for (int k=0; k<powers.size(); k++) {
        if (powers[k]== 285+move+1 | powers[k]== 285+move | powers[k]== 285+move-1) {
            stop = false;
        }
    }
}

void Ghost::get_ghost(int clock) {
    srand(time(0));
    random = rand()%15;
    if (rand()%clock + 1 == 1) {
        ghosts.push_back(random);
        if (random == 5) {
            ghosts.push_back(7);
            ghosts. push_back(10);
            ghosts.push_back(2);
            ghosts.push_back(12);
        } else if (random < 8) {
            ghosts.push_back(random+2);
            ghosts.push_back(random+5);
        } else {
            random = 2;
            for (int r=2; r<9; r=r+2) {
                ghosts.push_back(r);
        }
    }
    }
}

void Ship::get_shot(int shot) {
    shots.push_back(shot+285);
    shots.push_back(shot+284);
    shots.push_back(shot+286);
}

void Ship::ship_position() {
    Ship::shot_position();
    if (move==0) {move++;}
    if (move==14) {move--;}
    playground[283+move] = ' ';
    playground[287+move] = ' ';
    playground[286+move] = '+';
    playground[284+move] = '+';
    playground[285+move] = 'A';
    fade = move;
}

void Ship::shot_position() {
    for (int s=0; s<shots.size(); s++) {
        playground[shots[s]] = ' ';
        shots[s]=shots[s]-15;
        if (shots[s]%3==1) {
            playground[shots[s]] = '*';
        } else {
            playground[shots[s]] = '*';
        }
        if (shots[s]<0) {
            shots.erase(shots.begin()+s);
        }
    }
}

void Ship::display() {
    for (int n=0;n<15*20;n++) {
        cout << playground[n] << flush;
        if ((n+1)%15==0) {
            cout << endl;
        }
    }
}

void Ship::ship_move() {

    const int KEY_ARROW_CHAR1 = 224;
    const int KEY_ARROW_UP = 72;
    const int KEY_ARROW_DOWN = 80;
    const int KEY_ARROW_LEFT = 75;
    const int KEY_ARROW_RIGHT = 77;

    unsigned char ch1 = _getch();
    if (ch1 == KEY_ARROW_CHAR1)
    {
        unsigned char ch2 = _getch();
        switch (ch2){
        case KEY_ARROW_UP:
            Ship::get_shot(move);
            break;
        case KEY_ARROW_LEFT:
            move --;
            break;
        case KEY_ARROW_RIGHT:
            move++;
            break;
        case KEY_ARROW_DOWN:
            playground[140]= 'P';
            playground[141]= 'A';
            playground[142]= 'U';
            playground[143]= 'S';
            playground[144]= 'E';
            system("cls");
            display();
            Sleep(3000);
            while(true) {
            if (kbhit()){
                break;
            }
            }
            playground[140]= ' ';
            playground[141]= ' ';
            playground[142]= ' ';
            playground[143]= ' ';
            playground[144]= ' ';
        }
    }

}
