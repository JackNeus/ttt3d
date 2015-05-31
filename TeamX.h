#include <chrono>

#include <climits>
#include <vector>
#include "ttt3d.h"
#include <iostream>
using namespace std;
/*
    Due June 1, 2015
    Each player gets a total of 3 minutes as measured by time_used()
    (x,y,z) in {0, 1, 2, 3}^3
*/

class TeamX : public TTT3D {
public:
    struct Node;
    typedef vector<Node> vN;

    explicit TeamX(const duration<double> tta) : TTT3D(tta) {
        currentState = Node();
        //currentState.b[0][0][0] = currentState.b[1][1][1] = currentState.b[2][2][2] = currentState.b[3][3][3] = 1;
        //cout << isWin() << " " << currentState.isTerminal() << endl;
    }

    void add_piece(int mv[]){
        currentState.b[mv[0]][mv[1]][mv[2]] = -1;
    }

    void next_move(int mv[]) {
        if(mv[0] != -1) currentState.b[mv[0]][mv[1]][mv[2]] = -1;
        currentState.printBoard();
        cout << "Alphabeta-ing...\n";
        alphabeta(currentState, 1, INT_MIN, INT_MAX, 0, 1);
        mv[0] = currentState.lastMove[0];
        mv[1] = currentState.lastMove[1];
        mv[2] = currentState.lastMove[2];
        cout << "Done moving...\n";
    }

    void print(){
        currentState.printBoard();
    }

    int isWin(){
        return currentState.isTerminal();
    }

    struct Node{
        typedef vector<int> vi;
        typedef vector<vi> vii;
        typedef vector<vii> grid;

        grid b; //1 is us, -1 is opponent, 0 is unoccupied
        vi lastMove;

        Node(){
            b = grid(4, vii(4, vi(4, 0)));
            lastMove = vi(3, -1);
        }
        Node(grid g, vi last): b(g), lastMove(last) {}

        int isTerminal(){
            //Straight Line
            for(int i = 0; i < 4; i++){
                for(int k = 0; k < 4; k++){
                    int t = 0;
                    for(int z = 0; z < 4; z++){
                        t += b[i][z][k];
                    }
                    if(t == 4) return 1;
                    if(t == -4) return -1;  
                }
            }
            //Straight Line
            for(int j = 0; j < 4; j++){
                for(int k = 0; k < 4; k++){
                    int t = 0;
                    for(int z = 0; z < 4; z++){
                        t += b[z][j][k];
                    } 
                    if(t == 4) return 1;
                    if(t == -4) return -1;
                }
            }
            //Straight Line
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                    int t = 0;
                    for(int z = 0; z < 4; z++){
                        t += b[i][j][z];
                    }
                    if(t == 4) return 1;
                    if(t == -4) return -1;
                }
            }

            for(int i = 0; i < 4; i++){
                int t = 0;
                for(int j = 0; j < 4; j++){
                    t += b[i][j][j];
                }
                if(t == 4) return 1;
                if(t == -4) return -1;
            }
            for(int i = 0; i < 4; i++){
                int t = 0;
                for(int j = 0; j < 4; j++){
                    t += b[i][3 - j][j];
                }
                if(t == 4) return 1;
                if(t == -4) return -1;
            }
            for(int i = 0; i < 4; i++){
                int t = 0;
                for(int j = 0; j < 4; j++){
                    t += b[i][j][3 - j];
                }
                if(t == 4) return 1;
                if(t == -4) return -1;
            }
            for(int i = 0; i < 4; i++){
                int t = 0;
                for(int j = 0; j < 4; j++){
                    t += b[j][i][j];
                }
                if(t == 4) return 1;
                if(t == -4) return -1;
            }
            for(int i = 0; i < 4; i++){
                int t = 0;
                for(int j = 0; j < 4; j++){
                    t += b[j][i][3 - j];
                }
                if(t == 4) return 1;
                if(t == -4) return -1;
            }
            for(int i = 0; i < 4; i++){
                int t = 0;
                for(int j = 0; j < 4; j++){
                    t += b[3 - j][i][j];
                }
                if(t == 4) return 1;
                if(t == -4) return -1;
            }
            for(int i = 0; i < 4; i++){
                int t = 0;
                for(int j = 0; j < 4; j++){
                    t += b[j][j][i];
                }
                if(t == 4) return 1;
                if(t == -4) return -1;
            }
            for(int i = 0; i < 4; i++){
                int t = 0;
                for(int j = 0; j < 4; j++){
                    t += b[3 - j][j][i];
                }
                if(t == 4) return 1;
                if(t == -4) return -1;
            }
            for(int i = 0; i < 4; i++){
                int t = 0;
                for(int j = 0; j < 4; j++){
                    t += b[j][3 - j][i];
                }
                if(t == 4) return 1;
                if(t == -4) return -1;
            }
            int t = 0;
            for(int i = 0; i < 4; i++){
                t += b[i][i][i];
            }
            if(t == 4) return 1;
            if(t == -4) return -1;
            t = 0;
            for(int i = 0; i < 4; i++){
                t += b[i][i][3 - i];
            }
            if(t == 4) return 1;
            if(t == -4) return -1;
            t = 0;
            for(int i = 0; i < 4; i++){
                t += b[i][3 - i][i];
            }
            if(t == 4) return 1;
            if(t == -4) return -1;
            t = 0;
            for(int i = 0; i < 4; i++){
                t += b[3 - i][i][i];
            }
            if(t == 4) return 1;
            if(t == -4) return -1;
            return 0;
        }

        int heuristic(int player){ /// player 1 for us, -1 for them
            int heur = 0;

            for(int g = -1; g <= 1; g += 2){
                int IIIinarows = 0;
                grid space_used(4, vii(4, vi(4, 0))); /// is an empty space valuable, and is it a part of a 1, 2, 3, or 4 in a row
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        for (int k = 0; k < 4; ++k) {
                            space_used[i][j][k] = 0;
                            if (b[i][j][k] != 0) space_used[i][j][k] = 5; /// we don't want to count already used spaces
                        }
                    }
                }

                /// check for in a rows for us horizontally
                int o = (g == -1 ? 1 : -1);
                for (int j = 0; j < 4; ++j) { /// height
                    for (int k = 0; k < 4; ++k) { /// depth
                        int how_many = 0;
                        for (int z = 0; z < 4; ++z) { /// count how many squares we have in this horizontal segment
                            if (b[z][j][k] == o) { /// enemy piece. not possible to win for this segment
                                how_many = -1;
                                break;
                            }
                            else if (b[z][j][k] == g) ++how_many;
                        }
                        if (how_many == -1) continue;
                        //if (how_many == 4) return (g == -1 ? INT_MAX : INT_MIN);
                        if (how_many == 4) heur += g * 10000;
                        for (int z = 0; z < 4; ++z) { /// update space_used
                            if (space_used[z][j][k] < how_many) {
                                space_used[z][j][k] = how_many;
                            }
                        }
                    }
                }

                /// check vertical segments
                for (int j = 0; j < 4; ++j) { /// width
                    for (int k = 0; k < 4; ++k) { /// depth
                        int how_many = 0;
                        for (int z = 0; z < 4; ++z) { /// count how many squares we have in this vertical segment
                            if (b[j][z][k] == o) { /// enemy piece. not possible to win for this segment
                                how_many = -1;
                                break;
                            }
                            else if (b[j][z][k] == g) ++how_many;
                        }
                        if (how_many == -1) continue;
                        //if (how_many == 4) return (g == -1 ? INT_MAX : INT_MIN);
                        if (how_many == 4) heur += g * 10000;
                        for (int z = 0; z < 4; ++z) { /// update space_used
                            if (space_used[j][z][k] < how_many) {
                                space_used[j][z][k] = how_many;
                            }
                        }
                    }
                }


                /// check z-axis segments
                for (int j = 0; j < 4; ++j) { /// width
                    for (int k = 0; k < 4; ++k) { /// height
                        int how_many = 0;
                        for (int z = 0; z < 4; ++z) { /// count how many squares we have in this segment
                            if (b[j][k][z] == o) { /// enemy piece. not possible to win for this segment
                                how_many = -1;
                                break;
                            }
                            else if (b[j][k][z] == g) ++how_many;
                        }
                        if (how_many == -1) continue;
                        //if (how_many == 4) return (g == -1 ? INT_MAX : INT_MIN);
                        if (how_many == 4) heur += g * 10000;
                        for (int z = 0; z < 4; ++z) { /// update space_used
                            if (space_used[j][k][z] < how_many) {
                                space_used[j][k][z] = how_many;
                            }
                        }
                    }
                }

                /// check diagonal segments

                /// x-y diagonals
                for (int i = 0; i < 4; ++i) { /// vary depth
                    int how_many = 0;
                    for (int j = 0; j < 4; ++j) { /// forward diagonal
                        if (b[j][j][i] == o) {
                            how_many = -1;
                            break;
                        }
                        else if (b[j][j][i] == g) ++how_many;
                    }
                    if (how_many != -1) {
                        //if (how_many == 4) return (g == -1 ? INT_MAX : INT_MIN);
                        if (how_many == 4) heur += g * 10000;
                        for (int j = 0; j < 4; ++j) {
                            if (space_used[j][j][i] < how_many) {
                                space_used[j][j][i] = how_many;
                            }
                        }
                    }

                    how_many = 0;

                    for (int j = 0; j < 4; ++j) { /// backward diagonal
                        if (b[j][3 - j][i] == o) {
                            how_many = -1;
                            break;
                        }
                        else if (b[j][3 - j][i] == g) ++how_many;
                    }
                    if (how_many != -1) {
                        //if (how_many == 4) return (g == -1 ? INT_MAX : INT_MIN);
                        if (how_many == 4) heur += g * 10000;
                        for (int j = 0; j < 4; ++j) {
                            if (space_used[j][3 - j][i] < how_many) {
                                space_used[j][3 - j][i] = how_many;
                            }
                        }
                    }
                }

                /// y-z diagonals
                for (int i = 0; i < 4; ++i) { /// vary width
                    int how_many = 0;
                    for (int j = 0; j < 4; ++j) { /// forward diagonal
                        if (b[i][j][j] == o) {
                            how_many = -1;
                            break;
                        }
                        else if (b[i][j][j] == g) ++how_many;
                    }
                    if (how_many != -1) {
                        //if (how_many == 4) return (g == -1 ? INT_MAX : INT_MIN);
                        if (how_many == 4) heur += g * 10000;
                        for (int j = 0; j < 4; ++j) {
                            if (space_used[i][j][j] < how_many) {
                                space_used[i][j][j] = how_many;
                            }
                        }
                    }

                    how_many = 0;

                    for (int j = 0; j < 4; ++j) { /// backward diagonal
                        if (b[i][3 - j][j] == o) {
                            how_many = -1;
                            break;
                        }
                        else if (b[i][3 - j][j] == g) ++how_many;
                    }
                    if (how_many != -1) {
                        //if (how_many == 4) return (g == -1 ? INT_MAX : INT_MIN);
                        if (how_many == 4) heur += g * 10000;
                        for (int j = 0; j < 4; ++j) {
                            if (space_used[i][3 - j][j] < how_many) {
                                space_used[i][3 - j][j] = how_many;
                            }
                        }
                    }
                }

                /// x-z diagonals
                for (int i = 0; i < 4; ++i) { /// vary height
                    int how_many = 0;
                    for (int j = 0; j < 4; ++j) { /// forward diagonal
                        if (b[j][i][j] == o) {
                            how_many = -1;
                            break;
                        }
                        else if (b[j][i][j] == g) ++how_many;
                    }
                    if (how_many != -1) {
                        //if (how_many == 4) return (g == -1 ? INT_MAX : INT_MIN);
                        if (how_many == 4) heur += g * 10000;
                        for (int j = 0; j < 4; ++j) {
                            if (space_used[j][i][j] < how_many) {
                                space_used[j][i][j] = how_many;
                            }
                        }
                    }

                    how_many = 0;

                    for (int j = 0; j < 4; ++j) { /// backward diagonal
                        if (b[3 - j][i][j] == o) {
                            how_many = -1;
                            break;
                        }
                        else if (b[3 - j][i][j] == g) ++how_many;
                    }
                    if (how_many != -1) {
                        //if (how_many == 4) return (g == -1 ? INT_MAX : INT_MIN);
                        if (how_many == 4) heur += g * 10000;
                        for (int j = 0; j < 4; ++j) {
                            if (space_used[3 - j][i][j] < how_many) {
                                space_used[3 - j][i][j] = how_many;
                            }
                        }
                    }
                }

                /// 4 x-y-z diagonals
                for (int test = 0; test < 1; ++test) { /// I don't want how_many to be global in method
                    int how_many = 0;
                    for (int i = 0; i < 4; ++i) {
                        if (b[i][i][i] == o) {
                            how_many = -1;
                            break;
                        }
                        else if (b[i][i][i] == g) ++how_many;
                    }
                    if (how_many != -1) {
                        //if (how_many == 4) return (g == -1 ? INT_MAX : INT_MIN);
                        if (how_many == 4) heur += g * 10000;
                        for (int i = 0; i < 4; ++i) {
                            if (space_used[i][i][i] < how_many) {
                                space_used[i][i][i] = how_many;
                            }
                        }
                    }

                    how_many = 0;

                    for (int i = 0; i < 4; ++i) {
                        if (b[3 - i][3 - i][i] == o) {
                            how_many = -1;
                            break;
                        }
                        else if (b[3 - i][3 - i][i] == g) ++how_many;
                    }
                    if (how_many != -1) {
                        //if (how_many == 4) return (g == -1 ? INT_MAX : INT_MIN);
                        if (how_many == 4) heur += g * 10000;
                        for (int i = 0; i < 4; ++i) {
                            if (space_used[3 - i][3 - i][i] < how_many) {
                                space_used[3 - i][3 - i][i] = how_many;
                            }
                        }
                    }

                    how_many = 0;

                    for (int i = 0; i < 4; ++i) {
                        if (b[3 - i][i][i] == o) {
                            how_many = -1;
                            break;
                        }
                        else if (b[3 - i][i][i] == g) ++how_many;
                    }
                    if (how_many != -1) {
                        //if (how_many == 4) return (g == -1 ? INT_MAX : INT_MIN);
                        if (how_many == 4) heur += g * 10000;
                        for (int i = 0; i < 4; ++i) {
                            if (space_used[3 - i][i][i] < how_many) {
                                space_used[3 - i][i][i] = how_many;
                            }
                        }
                    }

                    how_many = 0;

                    for (int i = 0; i < 4; ++i) {
                        if (b[i][3 - i][i] == o) {
                            how_many = -1;
                            break;
                        }
                        else if (b[i][3 - i][i] == g) ++how_many;
                    }
                    if (how_many != -1) {
                        //if (how_many == 4) return (g == -1 ? INT_MAX : INT_MIN);
                        if (how_many == 4) heur += g * 10000;
                        for (int i = 0; i < 4; ++i) {
                            if (space_used[i][3 - i][i] < how_many) {
                                space_used[i][3 - i][i] = how_many;
                            }
                        }
                    }
                }

                /// add up everything to heuristic, and check for wins
                int posneg = (g == player ? 1 : -1);
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        for (int k = 0; k < 4; ++k) {
                            if (space_used[i][j][k] == 1) {
                                heur += g * 1;
                            }
                            else if (space_used[i][j][k] == 2) {
                                heur += g * 10;
                            }
                            else if (space_used[i][j][k] == 3) {
                                //++IIIinarows;
                                //if (IIIinarows > 1 || ((g == 1 &&  player == 1) || (g == -1 && player == 0)) ) { /// we have a fork, or it's our turn
                                    //if(g == player) {
                                        //return INT_MAX;
                                    //}
                                    //else return INT_MIN;
                                //}
                                heur += g * 1000;
                            }
                            else if (space_used[i][j][k] == 4) {
                                heur += g * 100000;
                                cout << "WHAT" << endl;
                            }
                        }
                    }
                }
            }

            return heur;
        }

        vector<Node> children(){
            vector<Node> childs;
            grid c = b;
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                    for(int k = 0; k < 4; k++){
                        if(b[i][j][k]) continue;
                        c = b;
                        c[i][j][k] = 1;
                        vi move(3);
                        move[0] = i;
                        move[1] = j;
                        move[2] = k;
                        Node n(c, move);
                        childs.push_back(n);
                    }
                }
            }
            return childs;
        }
        void printBoard(){
            for(int k = 0; k < 4; k++){
                for(int i = 0; i < 4; i++){
                    for(int j = 0; j < 4; j++){
                        if(b[j][i][k] == -1) cout << "X";
                        else if(b[j][i][k] == 1) cout << "O";
                        else cout << ".";
                    }
                    cout << "\t";
                }
                cout << "\n";
            }
            cout << "\n";
        }
    };

    Node currentState;

    int alphabeta(Node n, int depth, int alpha, int beta, int player, bool root) {
        if (depth == 0 || n.isTerminal() != 0) {
            if(root) currentState = n;
            return -1 * n.heuristic(!player);
        }

        if (player == 1) { /// MAXIMIZING PLAYER
            int v = INT_MIN;
            vN children = n.children();
            Node nextMove;
            for (int i = 0; i < children.size(); ++i) {
                int t = alphabeta(children[i], depth - 1, alpha, beta, -1, false);
                if(t > v){
                    v = t;
                    nextMove = children[i];
                }
                alpha = max(alpha, v);
                if (beta <= alpha) {
                    break;
                }
            }
            if(root) currentState = nextMove;
            return v;
        }
        else { /// MINIMIZER
            int v = INT_MAX;
            vN children = n.children();
            Node nextMove;
            for (int i = 0; i < children.size(); ++i) {
                int t = alphabeta(children[i], depth - 1, alpha, beta, 1, false);
                if(t < v){
                    v = t;
                    nextMove = children[i];
                }
                beta = min(beta, v);
                if (beta <= alpha) {
                    break;
                }
            }
            if(root) currentState = nextMove;
            return v;
        }

        /*if (depth == 0 || n.isTerminal()) {
            int t = n.heuristic(!player);
            if(root) currentState = n;
            return t;
        }
        vN children = n.children();
        int v = INT_MIN;
        Node nextMove;
        for (int i = 0; i < children.size(); ++i) {
            int t = alphabeta(children[i], depth - 1, alpha, beta, false, false);
            if(t > v){
                v = t;
                nextMove = children[i];
            }
            int a = max(alpha, v);
            if (beta <= alpha) {
                break;
            }
        }
        if(root) currentState = nextMove;
        return v; */
    }

};
