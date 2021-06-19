//
// Created by galwe on 18/06/2021.
//
const int SNIPER_AMMO_UP=2;
const char SNIPER_CROSS_LETTER='n';
const char SNIPER_POWER_LETTER='N';
const int SNIPER_MAX_MOVE=4;
const int REGULAR=1;
const int DOUBLE=2;
#include "Sniper.h"
namespace mtm {
    void Sniper::reload() {
        this->ammo += SNIPER_AMMO_UP;
    }


    char Sniper::getLetter() {
        if (this->team == CROSSFITTERS) {
            return SNIPER_CROSS_LETTER;
        } else {
            return SNIPER_POWER_LETTER;
        }
    }

    int Sniper::getMaxMove() {
        return SNIPER_MAX_MOVE;
    }

    int Sniper::hitMultiplier() {
        if (this->hit == SECOND) {
            this->hit = ZERO;
            return DOUBLE;
        }
        if (this->hit == FIRST) {
            this->hit = SECOND;
            return REGULAR;
        }
        if (this->hit == ZERO) {
            this->hit = FIRST;
            return REGULAR;
        }
        return REGULAR;
    }

    std::shared_ptr<Character> Sniper::clone() const {
        return std::shared_ptr<Character>(new Sniper(this->team,this->health,
                                                     this->ammo, this->range,this->power, this->hit));
    }
}