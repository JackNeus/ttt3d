#include <chrono>

#include <climits>
#include <vector>
#include "ttt3d.h"
using namespace std;
/*
    Due June 1, 2015
    Each player gets a total of 3 minutes as measured by time_used()
    (x,y,z) in {0, 1, 2, 3}^3
*/

class TeamX : public TTT3D {
public:  

    explicit TeamX(const duration<double> tta) : TTT3D(tta) {

    }

    void next_move(int mv[]) {

    }

private:
    struct Node{

        typedef vector<int> vi;
        typedef vector<vi> vii;
        typedef vector<vii> grid;

        grid b; //1 is us, -1 is opponent, 0 is unoccupied
        Node(){
            b = grid(4, vii(4, vi(4, 0)));
        }
        bool isTerminal(){
            return true;
        }
        int heuristic(){
            return 0;
        }
        vector<Node> children(){

        }
    };
    typedef vector<Node> vN;
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
