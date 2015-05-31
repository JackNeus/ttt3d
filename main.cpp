#include "TeamX.h"
#include <iostream>
using namespace std;

int main() {
    auto length = minutes(3);
    auto players = new TTT3D*[3];

    //players[0] = new TeamX(length);

    TeamX player(length);
    //players[0]->init_clock();
    //players[0]->currentSate.grid[0][0][0] = 1;

    int moves[3];
    while(!player.isWin()){
    	player.print();
    	cout << "Enter move (x, y, z): ";
    	cin >> moves[0] >> moves[1] >> moves[2];
    	player.next_move(moves);
    }
    int p = player.isWin();
    if(p == -1) cout << "You Win!\n";
    else cout << "You Lose!\n";
/*
    int moves[3];
    cin >> moves[0] >> moves[1] >> moves[2];
    while(moves[0] != -1){
    	player.add_piece(moves);
    	player.print();
    	cout << player.isWin() << endl;
    	if(player.isWin() != 0){
    		cout << "Game over." << endl;
    		return 0;
    	}
    	cin >> moves[0] >> moves[1] >> moves[2];
    }*/
}
