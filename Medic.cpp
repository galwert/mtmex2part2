//
// Created by galwe on 18/06/2021.
//
const int MEDIC_AMMO_UP=5;
const char MEDIC_CROSS_LETTER='m';
const char MEDIC_POWER_LETTER='M';
const int MEDIC_MAX_MOVE=5;
#include "Medic.h"
namespace mtm {
    void Medic::reload() {
        this->ammo += MEDIC_AMMO_UP;
    }


    char Medic::getLetter() {
        if (this->team == CROSSFITTERS) {
            return MEDIC_CROSS_LETTER;
        } else {
            return MEDIC_POWER_LETTER;
        }
    }
    int Medic::getMaxMove() {
        return MEDIC_MAX_MOVE;
    }

    std::shared_ptr<Character> Medic::clone() const {
        return std::shared_ptr<Character>(new Medic(*this));
    }
}