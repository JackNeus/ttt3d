#include "TeamX.h"
#include <iostream>
using namespace std;

int main() {
    auto length = minutes(3);
    auto players = new TTT3D*[3];

    players[0] = new TeamX(length);
    players[0]->init_clock();
}
