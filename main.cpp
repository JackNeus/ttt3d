#include "ttt3d.h"
#include "TeamX.h"

class TeamX : public TTT3D {
public:
    explicit TeamX(const duration<double> tta) : TTT3D(tta) {

    }

    void next_move(int mv[]) {

    }
};

int main() {
    auto length = minutes(3);
    auto players = new TTT3D*[3];

    players[0] = new TeamX(length);
    players[0]->init_clock();
}
