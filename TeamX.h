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
        }
        Node(grid g, vi last): b(g), lastMove(last) {}

        bool isTerminal(){
            return true;
        }
        int heuristic(){
            int heur = 0;
            int space_used[4][4][4]; /// is an empty space valuable, and is it a part of a 1, 2, or 3 in a row
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    for (int k = 0; k < 4; ++k) {
                        space_used[i][j][k] = 0;
                    }
                }
            }

            /// check for in a rows for us horizontally
            for (int j = 0; j < 4; ++j) { /// height
                for (int k = 0; k < 4; ++k) { /// depth
                    int how_many = 0;
                    for (int z = 0; z < 4; ++z) { /// count how many squares we have in this horizontal segment
                        if (grid[z][j][k] == -1) { /// enemy piece. not possible to win for this segment
                            how_many == -1;
                            break;
                        }
                        else if (grid[z][j][k] == 1) ++how_many;
                    }
                    if (how_many == -1) continue;
                    for (int z = 0; z < 4; ++z) { /// update space_used
                        if (space_used[i] < how_many) {
                            space_used[i] = how_many;
                        }
                    }
                }
            }

            /// check vertical segments
            //
            //
            //
            /// check z-axis segments

            /// check diagonal segments

            /// add up everything to heuristic
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    for (int k = 0; k < 4; ++k) {
                        if (space_used[i][j][k] == 1) {
                            heur += 1;
                        }
                        else if (space_used[i][j][k] == 2) {
                            heur += 10;
                        }
                        else if (space_used[i][j][k] == 3) {
                            heur += 100;
                        }
                    }
                }
            }

            /// reset space used for opponent's squares
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    for (int k = 0; k < 4; ++k) {
                        space_used[i][j][k] = 0;
                    }
                }
            }

            return hstc;

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
            return n.heuristic();
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
