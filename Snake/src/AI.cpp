#include "AI.h"
#include <vector>
#include <iostream>

using namespace std;

void AI::run_game() {
    init_map();
    display();
}

void AI::init_map(){
    for (int i=0; i<400; i++) {
        surface.push_back('.');
    }
}

void AI::display_map(){
    for (int i=0; i<400; i++) {
        cout << surface[i] << flush;
        if (i+1==40) {
            cout << endl;
        }
    }
}
