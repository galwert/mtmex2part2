
#include "Character.h"
namespace mtm {
    bool Character::lowerHealth(int hit_points)
    {
        if (this->health <= hit_points)
            return true;
        this->health -= hit_points;
        return false;
    }

    Team Character::getTeam() {
        return this->team;
    }

    int Character::getPower() const {
        return power;
    }

    void Character::lowerAmmo() {
        this->ammo--;
    }

    int Character::getAmmo() const {
        return this->ammo;
    }

    int Character::getRange() const {
        return this->range;
    }

     int Character::hitMultiplier() {
        return 0;
    }
}