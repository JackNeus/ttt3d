#include <chrono>

#include <climits>
#include "ttt3d.h"
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

    struct node{
        int b[4][4][4];
    };

    int alphabeta(node n, int depth, int alpha, int beta, bool maximizingPlayer) {
        if (depth == 0 || node.isTerminal()) {
            return node.heuristic();
        }
        if (maximizingPlayer) {
            int v = INT_MIN;
            for (int i = 0; i < n.childs; ++i) {
                v = max(v, alphabeta(n.child[i], depth - 1, alpha, beta, false));
                int a = max(alpha, v);
                if (beta <= alpha) {
                    break;
                }
            }
            return v;
        }
        else {
            int v = INT_MAX;
            for (int i = 0; i < n.childs. ++i) {
                v = min(v, alphabeta(child, depth - 1, alpha, beta, true));
                beta = min(beta, v);
                if (beta <= alpha) {
                    break;
                }
            }
            return v;
        }
    }

private:



};
