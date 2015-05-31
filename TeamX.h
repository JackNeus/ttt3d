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
        currentState.printBoard();
        vN c = currentState.children();

    }

    void next_move(int mv[]) {

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
            b[0][0][0] = 1;
            b[2][0][2] = -1;
            cout << "calling " << heuristic(0) << endl;
        }
        Node(grid g, vi last): b(g), lastMove(last) {}

        bool isTerminal(){
            return true;
        }

        int heuristic(int player){ /// player 1 for us, 0 for them
            int heur = 0;

            for(int g = 1; g <= 1; g += 2){
                int IIIinarows = 0;
                grid space_used(4, vii(4, vi(4, 0))); /// is an empty space valuable, and is it a part of a 1, 2, or 3 in a row
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        for (int k = 0; k < 4; ++k) {
                            space_used[i][j][k] = 0;
                            if (b[i][j][k] != 0) space_used[i][j][k] = 4; /// we don't want to count already used spaces
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
                                cout << "FOUND YOU 1" << endl;
                                if (how_many == 1) cout << "SHH" << endl;
                                break;
                            }
                            else if (b[z][j][k] == g) ++how_many;
                        }
                        if (how_many == -1) continue;
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
                                cout << "FOUND YOU 2" << endl;
                                if (how_many == 1) cout << "SHH" << endl;
                                break;
                            }
                            else if (b[j][z][k] == g) ++how_many;
                        }
                        if (how_many == -1) continue;
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
                                cout << "FOUND YOU 3" << endl;
                                if (how_many == 1) cout << "SHH" << endl;
                                break;
                            }
                            else if (b[j][k][z] == g) ++how_many;
                        }
                        if (how_many == -1) continue;
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
                            cout << "FOUND YOU 4" << endl;
                            if (how_many == 1) cout << "SHH" << endl;
                            break;
                        }
                        else if (b[j][j][i] == g) ++how_many;
                    }
                    if (how_many != -1) {
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
                            cout << "FOUND YOU 5" << endl;
                            if (how_many == 1) cout << "SHH" << endl;
                            break;
                        }
                        else if (b[j][3 - j][i] == g) ++how_many;
                    }
                    if (how_many != -1) {
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
                            cout << "FOUND YOU 6" << endl;
                            if (how_many == 1) cout << "SHH" << endl;
                            break;
                        }
                        else if (b[i][j][j] == g) ++how_many;
                    }
                    if (how_many != -1) {
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
                            cout << "FOUND YOU 7" << endl;
                            if (how_many == 1) cout << "SHH" << endl;
                            break;
                        }
                        else if (b[i][3 - j][j] == g) ++how_many;
                    }
                    if (how_many != -1) {
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
                            cout << "FOUND YOU 8" << endl;
                            if (how_many == 1) cout << "SHH" << endl;
                            break;
                        }
                        else if (b[j][i][j] == g) ++how_many;
                    }
                    if (how_many != -1) {
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
                            cout << "FOUND YOU 9" << endl;
                            if (how_many == 1) cout << "SHH" << endl;
                            break;
                        }
                        else if (b[3 - j][i][j] == g) ++how_many;
                    }
                    if (how_many != -1) {
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
                            cout << "FOUND YOU 10" << endl;
                            if (how_many == 1) cout << "SHH" << endl;
                            break;
                        }
                        else if (b[i][i][i] == g) ++how_many;
                    }
                    if (how_many != -1) {
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
                            cout << "FOUND YOU 11" << endl;
                            if (how_many == 1) cout << "SHH" << endl;
                            break;
                        }
                        else if (b[3 - i][3 - i][i] == g) ++how_many;
                    }
                    if (how_many != -1) {
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
                            cout << "FOUND YOU 12" << endl;
                            if (how_many == 1) cout << "SHH" << endl;
                            break;
                        }
                        else if (b[3 - i][i][i] == g) ++how_many;
                    }
                    if (how_many != -1) {
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
                            cout << "FOUND YOU 13" << endl;
                            if (how_many == 1) cout << "SHH" << endl;
                            break;
                        }
                        else if (b[i][3 - i][i] == g) ++how_many;
                    }
                    if (how_many != -1) {
                        for (int i = 0; i < 4; ++i) {
                            if (space_used[i][3 - i][i] < how_many) {
                                space_used[i][3 - i][i] = how_many;
                            }
                        }
                    }
                }

                /// add up everything to heuristic, and check for wins
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
                                ++IIIinarows;
                                if (IIIinarows > 1 || ((g == 1 &&  player == 1) || (g == -1 && player == 0)) ) { /// we have a fork, or it's our turn
                                    if(g == 1) {
                                        cout << "WIN ";
                                        return INT_MAX;
                                    }
                                    if(g == -1) return INT_MIN;
                                }
                                heur += g * 100;
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
                        if(b[i][j][k] == -1) cout << "X";
                        else if(b[i][j][k] == 1) cout << "O";
                        else cout << ".";
                    }
                    cout << "\t";
                }
                cout << "\n";
            }
        }
    };

    Node currentState;

    int alphabeta(Node n, int depth, int alpha, int beta, bool maximizingPlayer) {
        if (depth == 0 || n.isTerminal()) {
            return n.heuristic(maximizingPlayer);
        }
        vN children = n.children();
        if (maximizingPlayer) {
            int v = INT_MIN;
            for (int i = 0; i < children.size(); ++i) {
                v = max(v, alphabeta(children[i], depth - 1, alpha, beta, false));
                int a = max(alpha, v);
                if (beta <= alpha) {
                    break;
                }
            }
            return v;
        }
        else {
            int v = INT_MAX;
            for (int i = 0; i < children.size(); ++i) {
                v = min(v, alphabeta(children[i], depth - 1, alpha, beta, true));
                beta = min(beta, v);
                if (beta <= alpha) {
                    break;
                }
            }
            return v;
        }
    }

};
