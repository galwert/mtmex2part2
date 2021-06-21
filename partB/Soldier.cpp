//
// Created by galwe on 18/06/2021.
//

#include "Soldier.h"
const int SOLDIER_AMMO_UP=3;
const char SOLDIER_CROSS_LETTER='s';
const char SOLDIER_POWER_LETTER='S';
const int SOLDIER_MAX_MOVE=3;
namespace mtm {
    void Soldier::reload() {
        this->ammo += SOLDIER_AMMO_UP;
    }


    char Soldier::getLetter() {
        if (this->team == CROSSFITTERS) {
            return SOLDIER_CROSS_LETTER;
        } else {
            return SOLDIER_POWER_LETTER;
        }
    }

    int Soldier::getMaxMove() {
        return SOLDIER_MAX_MOVE;
    }

    std::shared_ptr<Character> Soldier::clone() const {
        return std::shared_ptr<Character>(new Soldier(*this));
    }
}